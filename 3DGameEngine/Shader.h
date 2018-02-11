#ifndef SHADER_H
#define SHADER_H

#include <string>
using namespace std;
#include <GL\glew.h>
#include "Transform.h"
#include "Camera.h"

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

	void AddShader(const string& fileName, unsigned int type);

	void Bind();
	
	void Update(const Transform& transform, const Camera& camera);
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


