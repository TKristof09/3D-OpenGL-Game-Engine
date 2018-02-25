#include "Shader.h"
#include <iostream>
#include <fstream>


static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string&errorMessage);
static string LoadShader(const string& fileName);
static GLuint CreateShader(const string& text, unsigned int shaderType);


Shader::Shader()
{
	m_program = glCreateProgram();
}


Shader::~Shader()
{

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);

}

void Shader::AddShader(const string& fileName, unsigned int type)
{
	switch (type)
	{
		case GL_VERTEX_SHADER:
			m_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
			break;
		case GL_FRAGMENT_SHADER:
			m_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);
			break;
		case GL_GEOMETRY_SHADER:
			m_shaders[2] = CreateShader(LoadShader(fileName + ".geom"), GL_GEOMETRY_SHADER);
			break;
		default:
			std::cerr << "Shader type not specified" << endl;
			break;
	}


	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "textCoord");

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}	

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: program linking failed: ");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: program validation failed: ");

	
}
// TODO remove
void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

void Shader::SetUniform(const GLchar* uniform, float value)
{
	glUniform1f(glGetUniformLocation(m_program, uniform), value);
}

void Shader::SetUniform(const GLchar* uniform, const glm::vec3& value)
{
	glUniform3fv(glGetUniformLocation(m_program, uniform), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const GLchar* uniform, const glm::vec4& value)
{
	glUniform4fv(glGetUniformLocation(m_program, uniform), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const GLchar* uniform, const glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_program, uniform), 1, GL_FALSE, &value[0][0]);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

static GLuint CreateShader(const string& text, unsigned int shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
		cerr << "Error: Shader creation failed!" << endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStrings[0] = text.c_str();
	if (text.length() > pow(2, 31))
	{
		cerr << "text.length is greater than 2^31 so GLint can't hold it (shader.cpp line 65)" << endl;
	}
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

static string LoadShader(const string& fileName)
{
	ifstream file;
	file.open(fileName.c_str());

	string output;
	string line;

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
		cerr << "Unable to load shader:" << fileName << endl;
	}
	// only if need to debug
	// cout << output << endl;
	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string&errorMessage)
{
	GLint succes = 0;
	GLchar error[1024] = { 0 };

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

		cerr << errorMessage << ":" << error << "'" << endl;
	}
}