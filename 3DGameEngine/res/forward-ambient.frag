#version 330

out vec4 fragColor;

in vec2 textCoord0;

uniform vec3 ambientIntensity;
uniform sampler2D diffuse;

void main(){
	fragColor =  vec4(1.0, 0.5, 0.0, 1.0);
}
