#version 330

out vec4 fragColor;

in vec2 textCoord0;

uniform vec3 ambientIntensity;
uniform sampler2D diffuse;
uniform vec3 color;

void main(){
	fragColor = vec4(color, 1) * texture(diffuse, textCoord0.xy) * vec4(ambientIntensity, 1);
}
