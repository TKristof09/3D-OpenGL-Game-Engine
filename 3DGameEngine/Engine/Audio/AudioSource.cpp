#include "AudioSource.h"
#include "AudioEngine.h"

void AudioSource::AddToAudioEngine(AudioEngine* audioEngine)
{
    m_audioEngine = audioEngine;
    m_fmodSound = audioEngine->AddSound(m_name, m_mode);
}

void AudioSource::Play()
{
    m_channel = m_audioEngine->Play(m_name, m_volume);
    m_audioEngine->SetPaused(m_channel, m_paused);
    m_audioEngine->SetMute(m_channel, m_muted);
}

void AudioSource::SetVolume(float volume)
{
    volume <= 0.0f ? m_volume = 0 : m_volume = volume;
    std::cout << m_volume << std::endl;
    if(m_audioEngine && m_channel != -1)
        m_audioEngine->SetVolume(m_channel, m_volume);
}

void AudioSource::Mute(bool state)
{
    m_muted = state;
    if(m_audioEngine && m_channel != -1)
        m_audioEngine->SetMute(m_channel , m_muted);
}

void AudioSource::SetPaused(bool state)
{
    m_paused = state;
    if(m_audioEngine && m_channel != -1)
        m_audioEngine->SetPaused(m_channel, state);
}
