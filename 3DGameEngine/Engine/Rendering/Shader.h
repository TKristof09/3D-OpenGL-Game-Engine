#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL\glew.h>
#include "..\Core\Transform.h"
#include "..\Camera.h"
#include "Material.h"
#include "..\Core\RenderingEngine.h"


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

	void Bind();
	
    virtual void UpdateUniforms(const Transform& transform, /*const Camera& camera,*/ const Material& material, RenderingEngine* renderingEngine) {};
	void SetUniform(const GLchar* uniform, float value);
	void SetUniform(const GLchar* uniform, const glm::vec3& value);
	void SetUniform(const GLchar* uniform, const glm::vec4& value);
	void SetUniform(const GLchar* uniform, const glm::mat4& value);

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


