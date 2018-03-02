#ifndef FORWARD_SPOT_H
#define FORWARD_SPOT_H

#include "..\Shader.h"
#include "..\Material.h"
#include "SpotLight.h"

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
    void Bind()
    {
        Shader::Bind();
    };
    void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material &material, RenderingEngine* renderingEngine) override;
    void SetUniform(const GLchar* uniform, const PointLight& pointLight);
    void SetUniform(const GLchar* uniform, const Attenuation& attenuation);
    void SetUniform(const GLchar* uniform, const SpotLight& spotLight);
};



#endif // !FORWARD_SPOT_H

