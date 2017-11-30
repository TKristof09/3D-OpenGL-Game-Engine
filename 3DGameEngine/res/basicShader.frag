#version 330

out vec4 fragColor;
in vec2 textCoord0;

uniform sampler2D sampler;

void main(){
	fragColor = texture(sampler, textCoord0.xy);
}