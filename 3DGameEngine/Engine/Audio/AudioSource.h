#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include <string>
#include "../GameComponents/GameComponent.h"
#include <fmod/fmod.hpp>


class AudioSource : public GameComponent{
public:
    AudioSource(const std::string& soundFileName, float volume, bool loop = false)
    :m_name(soundFileName),
     m_mode(FMOD_DEFAULT | FMOD_LOOP_NORMAL),
     m_volume(volume),
     m_channel(-1),
     m_loop(loop),
     m_muted(false),
     m_paused(false){}

    void AddToAudioEngine(AudioEngine* audioEngine) override;

    void Play();
    /**
     * \brief Set the volume for this sound
     * \param volume linear volume level: 0 - 1
     */
    void SetVolume(float volume);
    void Mute(bool state);

    void Loop(bool value)
    {
        m_loop = value;
        if(value)
            m_mode = m_mode | FMOD_LOOP_NORMAL;
        else
            m_mode = m_mode | FMOD_LOOP_OFF;
    }


    void SetPaused(bool state);

private:
    AudioEngine* m_audioEngine;
    std::string m_name;
    FMOD_MODE m_mode;
    FMOD::Sound* m_fmodSound;
    float m_volume;
    short m_channel;
    
    bool m_loop;
    bool m_paused;
    bool m_muted;
};
#endif
