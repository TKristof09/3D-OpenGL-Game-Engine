#version 330 core

out vec4 fragColor;

in vec2 textCoord0;
in vec3 worldPos0;
in mat3 TBN0;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;


uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;

uniform vec3 eyePos;
uniform float ambientIntesnity;

uniform vec3 color;

vec3 GetNormalFromMap(){
	vec3 normal = texture(normalMap, textCoord0).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN0 * normal);
	return normal;
}
//calculate ratio between specular and diffuse with roughness integrated
vec3 FresnelSchlickRoughness(float cosHalfView, vec3 F0, float roughness){
	return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosHalfView, 5.0);
}

void main(){
	vec3 albedo     = pow(texture(albedoMap, textCoord0).rgb, vec3(2.2));
	vec3 normal = GetNormalFromMap();
	float metallic  = texture(metallicMap, textCoord0).r;
	float roughness = texture(roughnessMap, textCoord0).r;
    float ao        = texture(aoMap, textCoord0).r;

    vec3 viewDir = normalize(eyePos - worldPos0);
    vec3 reflectDir = reflect(-viewDir, normal);

	vec3 F0 = vec3(0.04); //this is good for every non-metallic
	F0      = mix(F0, albedo, metallic);
	vec3 kS = FresnelSchlickRoughness(max(dot(normal, viewDir), 0.0), F0, roughness);
	vec3 kD = 1.0 - kS;
	kD *= 1.0 - metallic;
	vec3 irradiance = texture(irradianceMap, worldPos0).rgb;
	vec3 diffuse    = irradiance * albedo * color;

   	const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, reflectDir,  roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf  = texture(brdfLUT, vec2(max(dot(normal, viewDir), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (kS * brdf.x + brdf.y);
	vec3 ambient = (kD * diffuse + specular) * ao; 

	ambient = ambient * ambientIntesnity;
	ambient = ambient / (ambient + vec3(1.0));
	ambient = pow(ambient, vec3(1.0 / 2.2));

	fragColor = vec4(ambient, 1.0);
}