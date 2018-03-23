#version 330

out vec4 fragColor;

in vec2 textCoord0;

uniform vec3 ambientIntensity;
uniform sampler2D diffuse;

void main(){
	fragColor = texture(diffuse, textCoord0.xy) * vec4(ambientIntensity, 1);
}
