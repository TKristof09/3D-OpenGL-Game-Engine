#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 MVP;

out vec3 WorldPos;

void main()
{
    WorldPos = aPos;

	vec4 clipPos = MVP * vec4(WorldPos, 1.0);

	gl_Position = clipPos;
}