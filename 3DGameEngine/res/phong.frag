#version 330

out vec4 fragColor;

in vec3 worldPos0;
in vec2 textCoord0;
in vec3 normal0;

struct BaseLight{
	
	vec3 color;
	float intensity;
};

struct DirectionalLight{
	BaseLight base;
	vec3 direction;
};

uniform vec3 eyePos;

uniform vec3 baseColor;
uniform vec3 ambientLight;
uniform sampler2D sampler;

uniform float specularIntensity;
uniform float specularExponent;

uniform DirectionalLight directionalLight;



vec4 CalcLight(BaseLight base, vec3 direction, vec3 normal){
	
	float diffuseFactor = dot(normal, -direction);
	
	vec4 diffuseColor = vec4(0,0,0,0);

	if(diffuseFactor > 0){
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor; 

		vec3 directionToEye = normalize(eyePos - worldPos0);
		vec3 reflectDirection = normalize(reflect(direction, normal));
	}

	return diffuseColor;
}

vec4 CalcDirectionalLight(DirectionalLight directionalLight, vec3 normal){
	return CalcLight(directionalLight.base, directionalLight.direction, normal);
}

void main(){
	
	vec4 totalLight = vec4(ambientLight,1);

	vec4 textureColor = texture(sampler, textCoord0.xy);
	
	vec4 color = vec4(baseColor,1);

	if(textureColor != vec4(0,0,0,0))
		color *= textureColor;

	vec3 normal = normalize(normal0);

	totalLight += CalcDirectionalLight(directionalLight, normal);

	fragColor = color * totalLight;
}