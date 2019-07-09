#include "Animator.h"
#include "../Core/Time.h"
#include <iostream>

void Animator::AddToGameObjectCallback()
{
    std::cout << GetGameObject()->name << " has an animator" << std::endl;

}

void Animator::Render(const Shader* shader, RenderingEngine* renderingEngine)
{
    UpdateAnimation();
}

void Animator::UpdateAnimation()
{
    IncreaseAnimationTime();
    for(auto pair : m_animation.GetChannels())
    {
        AnimationChannel* channel = pair.second;
        if(channel)
        {
            auto prevAndNext = FindPrevAndNextKeyFrames(*channel);
            float progression = GetProgression(prevAndNext);
            Interpolate(prevAndNext, progression, pair.first, channel);
        }
    }
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
        for(size_t i = 0; i < channel.keyframes.size(); i++)
        {
            next = const_cast<KeyFrame*>(&channel.keyframes[i]);
            if(next->timestamp > m_animationTime)
                break;
            prev = const_cast<KeyFrame*>(&channel.keyframes[i]);;
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
            m_prevKeyFrame = nullptr;
            res = FindPrevAndNextKeyFrames(channel);
        }

        return res;
    }
}

void Animator::Interpolate(const std::pair<KeyFrame*, KeyFrame*>& prevAndNext, float t, GameObject* go, AnimationChannel* channel)
{
    KeyFrame* prev = prevAndNext.first;
    KeyFrame* next = prevAndNext.second;

    //math::Vector3 prevTranslation;
    //math::Quaternion prevRotation;
    //math::Vector3 prevScale;

    //math::decompose(prev->bone->offsetmatrix, prevTranslation, prevRotation, prevScale);

    //math::Vector3 nextTranslation;
    //math::Quaternion nextRotation;
    //math::Vector3 nextScale;

    //math::decompose(next->bone->offsetmatrix, nextTranslation, nextRotation, nextScale);

    auto translation = math::lerp(prev->translation, next->translation, t);

    auto rotation = math::slerp(prev->rotation, next->rotation, t);

    auto scale = math::lerp(prev->scale, next->scale, t);

    Transform* transform = go->GetTransform();
    transform->SetPosition(translation);
    transform->SetRotation(math::normalize(rotation));
    transform->SetScale(scale);
    //std::cout << m_animationTime << " : "<<go->name << " : " << math::ToString(transform->GetWorldPosition()) <<
    //" : " << math::ToString(transform->GetWorldRotation()) <<
    //" : " << math::ToString(transform->GetWorldScale()) << std::endl;
	if(channel->bone)
	    channel->bone->finalTransform = m_globalInverse * transform->GetModel() * channel->bone->offsetMatrix;
}
