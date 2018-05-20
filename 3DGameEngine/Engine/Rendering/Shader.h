#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL\glew.h>
#include "..\Core\Transform.h"
#include "..\GameComponents\Camera.h"
#include "Material.h"

class RenderingEngine;

enum ShaderType
{
	VERTEXSHADER,
	FRAGMENTSHADER,
	GEOMETRYSHADER
};

class Shader
{
public:
	Shader();
	~Shader();

	void AddShader(const std::string& fileName, unsigned int type);

	void Bind() const;

	virtual void UpdateUniforms(const Transform& transform, /*const Camera& camera,*/ const Material& material,
	                            RenderingEngine* renderingEngine) const {};
	virtual void UpdateUniforms(RenderingEngine* renderingEngine, const Color& color, const Transform& transform) const {};
	void SetUniform(const std::string& uniform, float value) const;
	void SetUniform(const std::string& uniform, const math::Vector3& value) const;
	void SetUniform(const std::string& uniform, const math::Vector4& value) const;
	void SetUniform(const std::string& uniform, const math::Matrix4x4& value) const;

	inline GLuint GetUniformLocation(const GLchar* uniform) const
	{
		return glGetUniformLocation(m_program, uniform);
	};


private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};


#endif // !SHADER_H
