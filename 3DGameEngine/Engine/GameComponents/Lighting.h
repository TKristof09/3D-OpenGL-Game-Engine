#ifndef LIGHTING_H
#define LIGHTING_H

#include <glm\glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\component_wise.hpp>

#include "..\Engine\GameComponents\GameComponent.h"
#include "..\Rendering\Lighting\ForwardDirectional.h"
#include "..\Rendering\Lighting\ForwardPoint.h"
#include "..\Rendering\Lighting\ForwardSpot.h"

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

    BaseLight(const Color& color, float intensity, const Shader* shader) :
        m_color(color),
        m_intensity(intensity),
        m_shader(shader)
    {
    }

    virtual void AddToEngine(RenderingEngine* renderingEngine) override;

    inline const Color* GetColor() const { return &m_color; };
    inline const float* GetIntensity() const { return &m_intensity; };
    inline const Shader* GetShader() const { return m_shader; };

    inline void SetColor(const Color& color) { m_color = color; };
    inline void SetIntensity(const float intensity) { m_intensity = intensity; };

private:
    Color m_color;
    float m_intensity;
    const Shader* m_shader;
};

class DirectionalLight : public BaseLight
{
public:
    DirectionalLight(const Color& color = Color(0, 0, 0), float intensity = 0) :
        BaseLight(color, intensity, ForwardDirectional::GetInstance())
    {
    };

};



class PointLight : public BaseLight
{
public:
    PointLight(const Color& color = Color(0, 0, 0), const float intensity = 0, const Attenuation& attenuation = Attenuation(), const Shader* shader = ForwardPoint::GetInstance()) :
        BaseLight(color, intensity, shader),
        m_attenuation(attenuation)
    {
        const float a = m_attenuation.GetExponent();
        const float b = m_attenuation.GetLinear();
        const float c = m_attenuation.GetConstant() - COLOR_DEPTH * intensity * glm::max(color.r, glm::max(color.g, color.b));

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

    SpotLight(const Color& color = Color(0, 0, 0), const float intensity = 0, const Attenuation& attenuation = Attenuation(), float cutoff = 0) :
        PointLight(color, intensity, attenuation, ForwardSpot::GetInstance()),
        m_cutoff(cutoff)
    {
    }

    inline const float* GetCutoff() const { return &m_cutoff; };
    inline void SetCutoff(const float& cutoff) { m_cutoff = cutoff; };

private:
    float m_cutoff;

};

#endif // !LIGHTING_H