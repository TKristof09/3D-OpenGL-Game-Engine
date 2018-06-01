#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoord;

out vec2 textCoord0;
//out vec3 worldPos0;

uniform mat4 MVP;
uniform mat4 model;

void main(){
	gl_Position = MVP * vec4(position, 1.0);
	textCoord0 = textCoord;
	//worldPos0 = (model * vec4(position, 1.0)).xyz;
}