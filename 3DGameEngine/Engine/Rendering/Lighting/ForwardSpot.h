#ifndef FORWARD_SPOT_H
#define FORWARD_SPOT_H

#include "..\Shader.h"
#include "..\Material.h"

class RenderingEngine;
class SpotLight;
class PointLight;
class Attenuation;

class ForwardSpot : public Shader
{
public:
    ForwardSpot();
    ~ForwardSpot();
    static ForwardSpot* GetInstance()
    {

        static ForwardSpot instance;
        return &instance;
    }
    void Bind() const
    {
        Shader::Bind();
    };
    void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material &material, RenderingEngine* renderingEngine) const override;
    void SetUniform(const GLchar* uniform, const PointLight& pointLight) const;
    void SetUniform(const GLchar* uniform, const Attenuation& attenuation) const;
    void SetUniform(const GLchar* uniform, const SpotLight& spotLight) const;
};



#endif // !FORWARD_SPOT_H

