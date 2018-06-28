#include "AudioListener.h"
#include "AudioEngine.h"

void AudioListener::AddToAudioEngine(AudioEngine* audioEngine)
{
    m_audioEngine = audioEngine;
    
    audioEngine->SetListener(this);
}

math::Vector3 AudioListener::GetVelocity()
{
    math::Vector3 position = GetTransform()->GetWorldPosition();
    math::Vector3 velocity = lastPosition - position;
    lastPosition = position;
    return velocity;
}
