#version 330 core
layout (location = 0) in vec3 position;

out vec3 worldPos0;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    worldPos0 = position;
    gl_Position =  projection * view * vec4(worldPos0, 1.0);
}