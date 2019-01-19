#include "Animator.h"
#include "../Core/Time.h"

void Animator::AddToGameObjectCallback()
{
    auto children = GetGameObject()->GetChildren();
    for(GameObject* child : children)
    {
        AnimationChannel* anim = m_animation.GetChannel(child);
        if(anim)
            child->AddComponent(new Animator(&m_animation));
    }

}

void Animator::Render(const Shader* shader, RenderingEngine* renderingEngine)
{
    for(unsigned int i = 0; i < GetGameObject()->GetNumChildren(); ++i)
    {
        AnimationChannel* channel = m_animation.GetChannel(GetGameObject()->GetChild(i));
        if(channel)
            GetGameObject()->GetChild(i)->GetComponent<Animator>()->UpdateAnimation(*channel);
    }
}

void Animator::UpdateAnimation(const AnimationChannel& channel)
{
    IncreaseAnimationTime();
    auto prevAndNext = FindPrevAndNextKeyFrames(channel);
    float progression = GetProgression(prevAndNext);
    Interpolate(prevAndNext, progression);
}
void Animator::IncreaseAnimationTime()
{
    m_animationTime += Time::GetDelta();
    // Loop if the animation time is greater than the length of the clip
    if(m_animationTime > m_animation.GetLength())
        m_animationTime = std::fmod(m_animationTime, m_animation.GetLength());
}

float Animator::GetProgression(std::pair<KeyFrame*, KeyFrame*> prevAndNext)
{
    KeyFrame* prev = prevAndNext.first;
    KeyFrame* next = prevAndNext.second;
    float totalTime = next->timestamp - prev->timestamp;
    float currentTime = m_animationTime - prev->timestamp;

    return currentTime / totalTime;
}

std::pair<KeyFrame*, KeyFrame*> Animator::FindPrevAndNextKeyFrames(const AnimationChannel& channel)
{
    if(!m_prevKeyFrame)
    {
        // for some reason &channel.keyframes[0] is a const *
        KeyFrame* prev = const_cast<KeyFrame*>(&channel.keyframes[0]);
        KeyFrame* next = const_cast<KeyFrame*>(&channel.keyframes[0]);
        for(KeyFrame keyFrame : channel.keyframes)
        {
            next = &keyFrame;
            if(next->timestamp > m_animationTime)
            break;
            prev = &keyFrame;
        }
        m_prevKeyFrame = prev;
        return std::make_pair(prev,next);
    }

    else
    {
        std::pair<KeyFrame*, KeyFrame*> res;
        KeyFrame* next = m_prevKeyFrame + 1; 
        if(m_animationTime > m_prevKeyFrame->timestamp && m_animationTime < next->timestamp)
        {
            res = std::make_pair(m_prevKeyFrame, next);
            m_prevKeyFrame = next;
        }
        // somehow we skipped one or more keyframes so lets search for the keyframes the hard way
        else
        {
            res = FindPrevAndNextKeyFrames(channel);
        }

        return res;
    }
}

void Animator::Interpolate(const std::pair<KeyFrame*, KeyFrame*>& prevAndNext, float t)
{
    KeyFrame* prev = prevAndNext.first;
    KeyFrame* next = prevAndNext.second;

    GetTransform()->SetPosition(math::lerp(prev->transform.GetWorldPosition(), next->transform.GetWorldPosition(), t));

    GetTransform()->SetRotation(math::slerp(prev->transform.GetWorldRotation(), next->transform.GetWorldRotation(), t));

    GetTransform()->SetScale(math::lerp(prev->transform.GetWorldScale(), next->transform.GetWorldScale(), t));

}
