#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H
#include <FMod/fmod.hpp>
#include <map>
#include <iostream>
#include <3DMath/3DMath.h>
#include "AudioListener.h"

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    /**
     * \brief Call this once every frame
     */
    void Update();


    /**
     * \brief Set the audio listener of the engine(only 1 allowed)
     * \param listener 
     */
    void SetListener(AudioListener* listener);

    /**
     * \brief Load a sound into the audio engine
     * \param name name of the sound
     * \param mode 
     * \returns pointer to fmod sound
     */
    FMOD::Sound* AddSound(const std::string& name, FMOD_MODE mode);


    void RemoveSound(const std::string& name);


    /**
     * \brief Play a sound that is already loaded
     * \param name name of the sound to play
     * \return channel id for the sound or -1 if the sound isn't loaded
     */
    short Play(const std::string& name, float volume);
   

    // Units per meter. (Centimeters would be = 100)
    void SetDistanceFactor(float distanceFactor);


    /**
     * \brief Set the volume of a channel
     * \param channelID 
     * \param volume linear volume level: 0 - 1
     */
    void SetVolume(short channelID, float volume);


    /**
     * \brief Set the position and velocity of the audio listener for this channel
     * \param channelID 
     * \param position 
     * \param velocity 
     */
    void SetChannel3DPosition(short channelID, const math::Vector3& position, const math::Vector3& velocity);

    /**
     * \brief Pause the sound currently playing on the channel
     * \param channelID ID for the channel to pause
     * \param state true = pause, false = resume
     */
    void SetPaused(short channelID, bool state);

    /**
     * \brief Mute the sound playing on the channel
     * \param channelID 
     * \param state 
     */
    void SetMute(short channelID, bool state);

private:
    static int ErrorCheck(FMOD_RESULT result);

    FMOD_VECTOR ToFmodVector(const math::Vector3& v);

    FMOD::System* m_system;
    std::map<std::string, FMOD::Sound*> m_sounds;
    std::map<short, FMOD::Channel*> m_channels;
    short m_nextChannelID;
    float m_distanceFactor = 1.0f;

    AudioListener* m_listener;
};
#endif
