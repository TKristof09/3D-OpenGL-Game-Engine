#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Core/Transform.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Core/GameObject.h"
#include "../Rendering/Mesh.h"
struct KeyFrame
{
    float timestamp;
	// TODO maybe just store pos/rot/scale instead of transform
    math::Vector3 translation;
    math::Quaternion rotation;
    math::Vector3 scale;
    KeyFrame(float timestamp, const math::Vector3& translation, const math::Quaternion& rotation, const math::Vector3& scale):
        timestamp(timestamp),
        translation(translation),
        rotation(rotation),
        scale(scale){}
};

// Every bone has its own animation channel
struct AnimationChannel
{
    GameObject* object;
    Bone* bone;
    std::vector<KeyFrame> keyframes;
    AnimationChannel(GameObject* object, Bone* bone, std::vector<KeyFrame>& keyframes):
        object(object),
        bone(bone),
        keyframes(keyframes){}

};

class Animation
{
public:

    /**
     * duration: in ticks
	 * TODO might need to make the params double instead of float
     */
    Animation(const std::string& name, unsigned int duration, float tickspersec):
        m_duration(duration),
		m_tickspersec(tickspersec),
		m_name(name){
            std::cout<< "animation"<< std::endl;
        }

    ~Animation()
    {
        for(auto pair : m_channels)
        {
            delete &pair.second;
        }
    }
    void AddChannel(const AnimationChannel& channel)
    {
        m_channels.insert({channel.object, channel});
    }
    double GetLength()
    {
        return m_duration;
    }
    AnimationChannel* GetChannel(GameObject* object)
    {
        auto it = m_channels.find(object);
        if(it == m_channels.end())
        {
            std::cout << "Can't find channel for gameobject:" << object->name << std::endl;
            return nullptr;
        }
        else
            return &it->second;
    }
    const std::map<GameObject*, AnimationChannel>& GetChannels()
    {
        return m_channels;
    }
    std::string GetName() const
    {
        return m_name;
    }
private:
	std::string m_name;
	unsigned int m_duration;
	float m_tickspersec;
    std::map<GameObject*, AnimationChannel> m_channels;

};

#endif
