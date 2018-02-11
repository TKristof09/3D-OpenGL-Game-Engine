#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "Shader.h"
#include "Material.h"
#include "DirectionalLight.h"

class PhongShader : public Shader
{
public:
	PhongShader();
	~PhongShader();
	void Bind()
	{
		Shader::Bind();
	};
	
	void Update(const Transform& transform, const Camera& camera, const Material& material);
	void SetUniform(GLchar* uniform, const DirectionalLight& directionalLight);
	void SetUniform(GLchar* uniform, const BaseLight& baseLight);

	inline const glm::vec3* GetAmbientLight() const { return &ambientLight; };
	inline void SetAmbientLight(const glm::vec3& ambientLight) { this->ambientLight = ambientLight; };
	
	inline const DirectionalLight* GetDirectionalLight() const { return &directionalLight; };
	inline void SetDirectionalLight(const DirectionalLight& directionalLight) { this->directionalLight = directionalLight; };

private:
	Material m_material;
	glm::vec3 ambientLight;
	DirectionalLight directionalLight;
};



#endif // !PHONGSHADER_H

