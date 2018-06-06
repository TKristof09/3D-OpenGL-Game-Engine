#ifndef FORWARD_POINT_H
#define FORWARD_POINT_H

#include "..\Shader.h"
#include "..\Material.h"

class RenderingEngine;
class PointLight;
class Attenuation;

class ForwardPoint : public Shader
{
public:
	ForwardPoint();
	~ForwardPoint() = default;

	static ForwardPoint* GetInstance()
	{
		static ForwardPoint instance;
		return &instance;
	}
	void UpdateUniforms(const Transform& transform,/* const Camera& camera,*/ const Material& material,
	                    RenderingEngine* renderingEngine) const override;
	void SetUniform(std::string uniform, const PointLight& pointLight) const;
	void SetUniform(std::string uniform, const Attenuation& attenuation) const;
};


#endif // !FORWARD_POINT_H
