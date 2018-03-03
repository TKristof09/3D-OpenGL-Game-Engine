#ifndef LIGHTING_H
#define LIGHTING_H

#include <glm\glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\component_wise.hpp>

#include "..\Engine\GameComponents\GameComponent.h"
#include "ForwardAmbient.h"
#include "ForwardDirectional.h"
#include "ForwardPoint.h"
#include "ForwardSpot.h"

#define COLOR_DEPTH 256

class RenderingEngine;

class Attenuation
{
public:
    Attenuation(const float& exponent = 0, const float& linear = 0, const float& constant = 0)
    {
        m_exponent = exponent;
        m_linear = linear;
        m_constant = constant;
    };
    inline float GetExponent() const { return m_exponent; };
    inline float GetLinear() const { return m_linear; };
    inline float GetConstant() const { return m_constant; };

private:
    // exponent*x^2+linear*x+constant
    float m_exponent;
    float m_linear;
    float m_constant;
};

class BaseLight : public GameComponent
{
public:

    BaseLight(const glm::vec3& color, float intensity, const Shader* shader) :
        m_color(color),
        m_intensity(intensity),
        m_shader(shader)
    {}
    
    virtual void AddToEngine(RenderingEngine* renderingEngine);

    inline const glm::vec3* GetColor() const { return &m_color; };
    inline const float* GetIntensity() const { return &m_intensity; };
    inline const Shader* GetShader() const { return m_shader; };

    inline void SetColor(const glm::vec3& color) { m_color = color; };
    inline void SetIntensity(float intensity) { m_intensity = intensity; };

private:
    glm::vec3 m_color;
    float m_intensity;
    const Shader* m_shader;
};

class DirectionalLight : public BaseLight
{
public:
    DirectionalLight(const glm::vec3& color = glm::vec3(0, 0, 0), float intensity = 0) :
        BaseLight(color, intensity, ForwardDirectional::GetInstance()),
        m_direction(glm::normalize(*GetTransform()->GetRotation()))
    {};

    inline const glm::vec3* GetDirection() const { return &m_direction; };
    inline void SetDirection(const glm::vec3& direction) { m_direction = direction; };

private:
    glm::vec3 m_direction;

};



class PointLight : public BaseLight
{
public:
    PointLight(const glm::vec3& color = glm::vec3(0,0,0), float intensity = 0, const Attenuation& attenuation = Attenuation(), const Shader* shader = ForwardPoint::GetInstance()) :
        BaseLight(color, intensity, shader),
        m_attenuation(attenuation)
    {
        float a = m_attenuation.GetExponent();
        float b = m_attenuation.GetLinear();
        float c = m_attenuation.GetConstant() - COLOR_DEPTH * intensity * glm::compMax(color);

        m_range = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a);
    }

    inline const Attenuation* GetAttenuation() const { return &m_attenuation; };
    inline const float* GetRange() const { return &m_range; };

    inline void SetAttenuation(const Attenuation& attenuation) { m_attenuation = attenuation; };
    inline void SetRange(const float& range) { m_range = range; };

private:
    Attenuation m_attenuation;
    float m_range;

};


class SpotLight : public PointLight
{
public:

    SpotLight(const glm::vec3& color = glm::vec3(0, 0, 0), float intensity = 0, const Attenuation& attenuation = Attenuation(), float cutoff = 0) :
        PointLight(color, intensity, attenuation, ForwardSpot::GetInstance()),
        m_direction(glm::normalize(*GetTransform()->GetRotation())),
        m_cutoff(cutoff)
    {}

    inline const glm::vec3* GetDirection() const { return &m_direction; };
    inline const float* GetCutoff() const { return &m_cutoff; };

    inline void SetDirection(const glm::vec3& direction) { m_direction = direction; };
    inline void SetCutoff(const float& cutoff) { m_cutoff = cutoff; };

private:
    glm::vec3 m_direction;
    float m_cutoff;

};

#endif // !LIGHTING_H
