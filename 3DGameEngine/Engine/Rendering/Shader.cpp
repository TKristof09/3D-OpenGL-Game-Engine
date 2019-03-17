#include "Shader.h"
#include <iostream>
#include <fstream>


static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, unsigned int shaderType);


Shader::Shader()
{
	m_program = glCreateProgram();
}


Shader::~Shader()
{
	for (auto shader : m_shaders)
	{
		glDetachShader(m_program, shader);
		glDeleteShader(shader);
	}
	glDeleteProgram(m_program);
}

void Shader::AddShader(const std::string& fileName, unsigned int type)
{
	switch (type)
	{
		case GL_VERTEX_SHADER:
			m_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
			break;
		case GL_FRAGMENT_SHADER:
			m_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);
			break;
			//		case GL_GEOMETRY_SHADER:
			//			m_shaders[2] = CreateShader(LoadShader(fileName + ".geom"), GL_GEOMETRY_SHADER);
			//			break;
		default:
			std::cerr << "Shader type not specified" << std::endl;
			break;
	}

	
	for (auto shader : m_shaders)
	{
		glAttachShader(m_program, shader);
	}

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: program linking failed: " + fileName);

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: program validation failed: " + fileName);
}

void Shader::SetUniform(const std::string& uniform, int value) const
{
	GLuint loc;
	if (m_uniformMap.find(uniform) != m_uniformMap.end())
	{
		loc = m_uniformMap[uniform];
		glUniform1i(loc, value);
	}
	else
	{
		loc = glGetUniformLocation(m_program, uniform.c_str());
		glUniform1i(loc, value);
		m_uniformMap[uniform] = loc;
	}
}

void Shader::SetUniform(const std::string& uniform, float value) const
{
	GLuint loc;
	if(m_uniformMap.find(uniform) != m_uniformMap.end())
	{
		loc = m_uniformMap[uniform];
		glUniform1f(loc, value);
	}
	else
	{
		loc = glGetUniformLocation(m_program, uniform.c_str());
		glUniform1f(loc, value);
		m_uniformMap[uniform] = loc;
	}
}


void Shader::SetUniform(const std::string& uniform, const math::Vector3& value) const
{
	GLuint loc;
	if (m_uniformMap.find(uniform) != m_uniformMap.end())
	{
		loc = m_uniformMap[uniform];
		glUniform3fv(loc, 1, value_ptr(value));
	}
	else
	{
		loc = glGetUniformLocation(m_program, uniform.c_str());
		glUniform3fv(loc, 1, value_ptr(value));
		m_uniformMap[uniform] = loc;
	}
	
}

void Shader::SetUniform(const std::string& uniform, const math::Vector4& value) const
{
	GLuint loc;
	if (m_uniformMap.find(uniform) != m_uniformMap.end())
	{
		loc = m_uniformMap[uniform];
		glUniform4fv(loc, 1, value_ptr(value));
	}
	else
	{
		loc = glGetUniformLocation(m_program, uniform.c_str());
		glUniform4fv(loc, 1, value_ptr(value));
		m_uniformMap[uniform] = loc;
	}
}

void Shader::SetUniform(const std::string& uniform, const math::Matrix4x4& value) const
{
	GLuint loc;
	if (m_uniformMap.find(uniform) != m_uniformMap.end())
	{
		loc = m_uniformMap[uniform];
		glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
	}
	else
	{
		loc = glGetUniformLocation(m_program, uniform.c_str());
		glUniformMatrix4fv(loc, 1, GL_FALSE, &value[0][0]);
		m_uniformMap[uniform] = loc;
	}
	
}

void Shader::Bind() const
{
	glUseProgram(m_program);
}

static GLuint CreateShader(const std::string& text, unsigned int shaderType)
{
	const GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStrings[0] = text.c_str();
	if (text.length() > pow(2, 31))
	{
		std::cerr << "text.length is greater than 2^31 so GLint can't hold it (shader.cpp line 65)" << std::endl;
	}
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader:" << fileName << std::endl;
	}
	// only if need to debug
	// cout << output << endl;
	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint succes = 0;
	GLchar error[1024] = {0};

	if (isProgram)
		glGetProgramiv(shader, flag, &succes);
	else
		glGetShaderiv(shader, flag, &succes);

	if (succes == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << " : " << error << std::endl;
	}
}
