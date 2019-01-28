#include "AudioEngine.h"
//#include <Windows.h>
#include <vector>


AudioEngine::AudioEngine(): 
    m_nextChannelID(0),
    m_listener(nullptr)
{
    //CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    ErrorCheck(FMOD::System_Create(&m_system));
    unsigned int version;
    ErrorCheck(m_system->getVersion(&version));
    if (version < FMOD_VERSION)
    {
        std::cout << "FMOD lib version" << version << "doesn't match header version " << FMOD_VERSION << std::endl;
    }
    ErrorCheck(m_system->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, NULL));
    ErrorCheck(m_system->set3DSettings(1.0f, m_distanceFactor, 1.0f));
}

AudioEngine::~AudioEngine()
{
    for (auto pair : m_sounds)
    {
        pair.second->release();
    }
    ErrorCheck(m_system->close());
    ErrorCheck(m_system->release());
    //CoUninitialize();
}

void AudioEngine::ReInit()
{
    m_nextChannelID = 0;
    m_listener = nullptr;
    for (auto pair : m_sounds)
    {
        pair.second->release();
    }
    m_sounds.clear();
    m_channels.clear();
}

void AudioEngine::Update()
{
    //TODO necessary??
    std::vector<std::map<short, FMOD::Channel*>::iterator> stoppedChannels;
    for (auto it = m_channels.begin(), itEnd = m_channels.end(); it != itEnd; ++it)
    {
        bool bIsPlaying = false;
        it->second->isPlaying(&bIsPlaying);
        if (!bIsPlaying)
        {
            stoppedChannels.push_back(it);
        }
    }
    for (auto& it : stoppedChannels)
    {
        m_channels.erase(it);
    }
    FMOD_VECTOR pos = ToFmodVector(m_listener->GetTransform()->GetWorldPosition());
    FMOD_VECTOR vel = ToFmodVector(m_listener->GetVelocity());
    FMOD_VECTOR forward = ToFmodVector(m_listener->GetTransform()->GetForward());
    FMOD_VECTOR up = ToFmodVector(m_listener->GetTransform()->GetUp());

    ErrorCheck(m_system->set3DListenerAttributes(0, &pos, &vel, &forward, &up));
    ErrorCheck(m_system->update());
}

void AudioEngine::SetListener(AudioListener* listener)
{
    m_listener = listener;
}

FMOD::Sound* AudioEngine::AddSound(const std::string& name, FMOD_MODE mode)
{
    auto it = m_sounds.find(name);
    if (it == m_sounds.end())
    {
        m_sounds[name] = nullptr;
        ErrorCheck(m_system->createSound(name.c_str(), mode, 0, &m_sounds[name]));
    }
    return m_sounds[name];
}

void AudioEngine::RemoveSound(const std::string& name)
{
    auto it = m_sounds.find(name);
    if (it == m_sounds.end())
    {
        std::cerr << "Sound " << name.c_str() << " not found" << std::endl;
        return;
    }
    it->second->release();
    m_sounds.erase(it);
}

short AudioEngine::Play(const std::string& name, float volume)
{
    auto it = m_sounds.find(name);
    if (it == m_sounds.end())
    {
        std::cerr << "Sound " << name.c_str() << " not found" << std::endl;
        return -1;
    }
    short channelID = m_nextChannelID++;
    FMOD::Channel* channel = nullptr;
    ErrorCheck(m_system->playSound(it->second, nullptr, true, &channel));
    if (channel)
    {
        ErrorCheck(channel->setPaused(false));
        ErrorCheck(channel->setVolume(volume));
        m_channels[channelID] = channel;
    }
    return channelID;
}


void AudioEngine::SetDistanceFactor(float distanceFactor)
{
    m_distanceFactor = distanceFactor;
    ErrorCheck(m_system->set3DSettings(1.0f, distanceFactor, 1.0f));
}

void AudioEngine::SetVolume(short channelID, float volume)
{
    auto it = m_channels.find(channelID);
    if (it == m_channels.end())
    {
        std::cerr << "Channel " << channelID << " not found" << std::endl;
        return;
    }
    ErrorCheck(it->second->setVolume(volume));
}

void AudioEngine::SetChannel3DPosition(short channelID, const math::Vector3& position, const math::Vector3& velocity)
{
    auto it = m_channels.find(channelID);
    if (it == m_channels.end())
    {
        std::cerr << "Channel " << channelID << " not found" << std::endl;
        return;
    }
    FMOD_VECTOR pos = ToFmodVector(position);
    FMOD_VECTOR vel = ToFmodVector(velocity);
    ErrorCheck(it->second->set3DAttributes(&pos, &vel));
}

void AudioEngine::SetPaused(short channelID, bool state)
{
    m_channels[channelID]->setPaused(state);
}

void AudioEngine::SetMute(short channelID, bool state)
{
    m_channels[channelID]->setMute(state);
}

int AudioEngine::ErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        std::cerr << "FMOD ERROR " << result << std::endl;
        return 1;
    }
    return 0;
}

FMOD_VECTOR AudioEngine::ToFmodVector(const math::Vector3& v)
{
    FMOD_VECTOR result;
    result.x = v.x;
    result.y = v.y;
    result.z = v.z;
    return result;
}
