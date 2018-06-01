#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 textCoords;

out vec2 textCoords0;

void main(){
	textCoords0 = textCoords;
	gl_Position = vec4(position, 1.0);
}