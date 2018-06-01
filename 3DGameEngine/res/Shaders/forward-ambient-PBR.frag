#version 330 core

out vec4 fragColor;

in vec3 textCoord0;
in vec3 worldPos0;
in mat3 TBN0;

uniform samplerCube irradianceMap;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;


uniform vec3 eyePos;

vec3 GetNormalFromMap(){
	vec3 normal = texture(normalMap, textCoord0).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN0 * normal);
	return normal;
}
//calculate ratio between specular and diffuse with roughness integrated
vec3 FresnelSchlickRoughness(float cosHalfView, vec3 F0, float roughness){
	return F0 + (max(vec3(1.0 - roughness), F0)) * pow(1.0 - cosHalfView, 5.0);
}

void main(){

    vec3 viewDir = normalize(eyePos - worldPos0);

	vec3 albedo     = pow(texture(albedoMap, textCoord0).rgb, vec3(2.2));
	vec3 normal = GetNormalFromMap();
	float roughness = texture(roughnessMap, textCoord0).r;
    float ao        = texture(aoMap, textCoord0).r;
    vec3 ambient = texture(irradianceMap, normal);
	
	vec3 kS = FresnelSchlickRoughness(max(dot(normal, viewDir), 0.0), F0, roughness);
	vec3 kD = 1.0 - kS;
	vec3 irradiance = texture(irradianceMap, normal).rgb;
	vec3 diffuse    = irradiance * albedo;
	vec3 ambient    = (kD * diffuse) * ao; 

	fragColor = vec4(ambient, 1.0);
}