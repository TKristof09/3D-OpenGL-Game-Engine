#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "3DMath/3DMath.h"
#include <LinearMath/btTransform.h>
#include <LinearMath/btMotionState.h>
#include "../Rendering/DebugUI.h"
#include <iostream>

//Currently not in use
#define MAX_DISTANCE 1e6

#define MAX_SCALE 1e3

class Transform : public btMotionState
{
public:
    Transform(const math::Vector3& position = math::Vector3(0, 0, 0),
        const math::Quaternion& rotation = math::Quaternion(1, 0, 0, 0),
        const math::Vector3& scale = math::Vector3(1, 1, 1)) :
        m_parent(nullptr),
        m_position(position),
        m_rotation(rotation),
        m_scale(scale),
        m_eulerRotations(math::Vector3(0)) {};


    math::Matrix4x4 GetModel() const
    {
        //For the property editor
        if (m_rotation.ToEulerAngles() != m_eulerRotations)
        {
            if(m_lastEuler.x != m_eulerRotations.x)
                rotx = math::Quaternion(math::ToRadians(m_eulerRotations.x), math::Vector3(1, 0, 0));
            if (m_lastEuler.y != m_eulerRotations.y)
                roty = math::Quaternion(math::ToRadians(m_eulerRotations.y), math::Vector3(0, 1, 0));
            if (m_lastEuler.z != m_eulerRotations.z)
                rotz = math::Quaternion(math::ToRadians(m_eulerRotations.z), math::Vector3(0, 0, -1));

            m_rotation = math::normalize(rotz * roty * rotx);
            m_lastEuler = m_eulerRotations;
        }

        math::Matrix4x4 translationMatrix = translate(m_position);

        math::Matrix4x4 rotationMatrix = ToMatrix4x4(m_rotation);

        math::Matrix4x4 scaleMatrix = scale(m_scale);

        return GetParentMatrix() * translationMatrix * rotationMatrix * scaleMatrix;
    };


    math::Vector3 GetPosition() const { return m_position; };
    math::Quaternion GetRotation() const { return m_rotation; };
    math::Vector3 GetScale() const { return m_scale; };

    math::Vector3 GetWorldPosition() const
    {
        return GetParentMatrix() * math::Vector4(m_position, 1);
    };

    math::Quaternion GetWorldRotation() const
    {
        if (m_parent)
            return m_rotation * m_parent->GetWorldRotation();
        else
            return m_rotation;
    };

    math::Vector3 GetWorldScale() const
    {
        if (m_parent)
            return m_scale * m_parent->GetWorldScale();
        else
            return m_scale;
    };

    math::Vector3 GetForward() const
    {
        return math::normalize(GetWorldRotation().GetForward());
    };
    math::Vector3 GetUp() const
    {
        return math::normalize(GetWorldRotation().GetUp());
    };
    math::Vector3 GetRight() const
    {
        return math::normalize(GetWorldRotation().GetRight());
    };

    void SetPosition(const math::Vector3& position) { m_position = position; };
    void SetRotation(const math::Quaternion& rotation) { m_rotation = rotation; };
    void SetScale(const math::Vector3& scale) { m_scale = scale; };
    void SetParent(Transform* parent) { m_parent = parent; };

    void Rotate(const math::Quaternion& rotation)
    {
        m_rotation = normalize(rotation * m_rotation);
        m_eulerRotations = m_rotation.ToEulerAngles();
    }

    void Rotate(float angle, const math::Vector3 axis)
    {
        Rotate(math::Quaternion(angle, axis));
    }

    void Translate(const math::Vector3& vector)
    {
        m_position += vector;
    }

    void Translate(const math::Vector3& direction, float amount)
    {
        Translate(direction * amount);
    }

    btTransform ToBtTransform() const
    {
        return btTransform(GetWorldRotation().ToBtQuaternion(), GetWorldPosition().ToBtVector3());
    }

    void AddToPropertyUIS(DebugUIWindow* hierarchyWindow) const
    {
        hierarchyWindow->AddElement(new DragVector3(const_cast<math::Vector3*>(&m_position), "Position"), 2);

        hierarchyWindow->AddElement(new DragVector3(const_cast<math::Vector3*>(&m_eulerRotations), "Rotation", -360, 360), 2);

        hierarchyWindow->AddElement(new DragVector3(const_cast<math::Vector3*>(&m_scale), "Scale", 0, MAX_SCALE), 2);

        hierarchyWindow->AddElement(new Separator());
    }

private:

    math::Matrix4x4 GetParentMatrix() const
    {
        if (m_parent != nullptr)
        {
            return m_parent->GetModel();
        }

        return math::Matrix4x4();
    }


    //btMotionState functions needed for bullet physics to work
public:
    void getWorldTransform(btTransform& worldTrans) const override
    {
        worldTrans.setOrigin(GetWorldPosition().ToBtVector3());
        worldTrans.setRotation(GetWorldRotation().ToBtQuaternion());
    };
    void setWorldTransform(const btTransform& worldTrans) override
    {
        m_position = worldTrans.getOrigin() - m_parent->GetWorldPosition().ToBtVector3();
        m_rotation = worldTrans.getRotation() * math::inverse(m_parent->GetWorldRotation()).ToBtQuaternion();
    }

private:
    Transform * m_parent;


    math::Vector3 m_position;
    mutable math::Quaternion m_rotation;
    math::Vector3 m_scale;
    math::Vector3 m_eulerRotations;
    mutable math::Vector3 m_lastEuler;
    mutable math::Quaternion rotx;
    mutable math::Quaternion roty;
    mutable math::Quaternion rotz;
};


#endif // !TRANSFORM_H
