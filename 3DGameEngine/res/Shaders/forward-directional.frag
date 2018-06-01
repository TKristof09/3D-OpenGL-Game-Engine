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

uniform sampler2D diffuse;
uniform sampler2D specular;

uniform float specularExponent;

uniform DirectionalLight directionalLight;

uniform vec3 color;

vec4 CalcLight(BaseLight base,vec3 direction){
	// ambient

    // diffuse 
    vec3 norm = normalize(normal0);
    vec3 lightDir = normalize(-direction);  
    float angle = clamp(dot(norm, lightDir), 0.0, 1.0);
    vec3 color = angle * base.color * base.intensity;
    
    // specular
    vec3 viewDir = normalize(eyePos - worldPos0);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), specularExponent);
    vec3 specular = specularFactor * base.color * texture(specular, textCoord0).rgb;  
        
    vec3 result = color + specular;
    return vec4(result,1.0);
}

vec4 CalcDirectionalLight(DirectionalLight directionalLight){
	return CalcLight(directionalLight.base, directionalLight.direction);
}

void main()
{
	fragColor = vec4(color, 1) * CalcDirectionalLight(directionalLight) *  texture(diffuse, textCoord0.xy);
} 
