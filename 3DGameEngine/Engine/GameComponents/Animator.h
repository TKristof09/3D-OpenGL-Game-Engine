#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "GameComponent.h"
#include "Animation.h"

class Animator : public GameComponent
{
public:
    Animator(Animation* animation):
        m_animation(*animation),
        m_animationTime(0.0f),
        m_prevKeyFrame(nullptr){}

    void AddToGameObjectCallback() override;
    void Render(const Shader* shader, RenderingEngine* renderingEngine) override;
    void UpdateAnimation(const AnimationChannel& channel);

private:
    void IncreaseAnimationTime();
    std::pair<KeyFrame*, KeyFrame*> FindPrevAndNextKeyFrames(const AnimationChannel& channel);
    float GetProgression(std::pair<KeyFrame*, KeyFrame*> prevAndNext);
    void Interpolate(const std::pair<KeyFrame*, KeyFrame*>& prevAndNext, float t);
    Animation m_animation;
    float m_animationTime;
    KeyFrame* m_prevKeyFrame;
};

#endif