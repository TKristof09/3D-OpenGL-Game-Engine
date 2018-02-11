#version 330

out vec4 fragColor;
in vec2 textCoord0;
in vec3 normal0;

uniform sampler2D sampler;
uniform vec3 color;

void main(){
	fragColor = texture(sampler, textCoord0.xy) * vec4(color,1);
}