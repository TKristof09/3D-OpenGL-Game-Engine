#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "GameComponent.h"
#include "Animation.h"

// A gameobject with an animator component animates itself and its children but not its grandchildren
class Animator : public GameComponent
{
public:
    Animator(Animation* animation, const math::Matrix4x4& globalInverse):
        m_animation(*animation),
        m_animationTime(0.0f),
        m_prevKeyFrame(nullptr),
        m_globalInverse(globalInverse){}

    void AddToGameObjectCallback() override;
    void Render(const Shader* shader, RenderingEngine* renderingEngine) override;
    void UpdateAnimation();

private:
    void IncreaseAnimationTime();
    std::pair<KeyFrame*, KeyFrame*> FindPrevAndNextKeyFrames(const AnimationChannel& channel);
    float GetProgression(std::pair<KeyFrame*, KeyFrame*> prevAndNext);
    void Interpolate(const std::pair<KeyFrame*, KeyFrame*>& prevAndNext, float t, GameObject* go, AnimationChannel* channel);
    Animation m_animation;
    float m_animationTime;
    KeyFrame* m_prevKeyFrame;
    math::Matrix4x4 m_globalInverse;
};

#endif
