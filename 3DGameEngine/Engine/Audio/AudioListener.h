#ifndef AUDIOLISTENER_H
#define AUDIOLISTENER_H
#include "../GameComponents/GameComponent.h"


class AudioListener : public GameComponent {
public:

    void AddToAudioEngine(AudioEngine* audioEngine) override;
    
    math::Vector3 GetVelocity();

private:
    math::Vector3 lastPosition;
    
    AudioEngine* m_audioEngine = nullptr;
    
};
#endif
