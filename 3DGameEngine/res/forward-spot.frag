#version 330

out vec4 fragColor;

in vec3 worldPos0;
in vec2 textCoord0;
in vec3 normal0;

struct BaseLight{
	
	vec3 color;
	float intensity;
};

struct Attenuation{
	// exponent*x^2+linear*x+constant
	float exponent;
	float linear;
	float constant;
};

struct PointLight{
	BaseLight base;
	Attenuation attenuation;
	vec3 position;
	float range;
};

struct SpotLight{
	PointLight pointLight;
	vec3 direction;
	float cutoff;
};

uniform vec3 eyePos;

uniform sampler2D sampler;

uniform float specularIntensity;
uniform float specularExponent;

uniform SpotLight spotLight;

vec4 CalcLight(BaseLight base,vec3 direction){
	// TODO idk why this is needed but it is 
	direction = normalize(-direction);
	// ambient

    // diffuse 
    vec3 norm = normalize(normal0);
    float angle = max(dot(norm, direction), 0.0);
    vec3 diffuse = angle * base.color * base.intensity;
    
    // specular
    vec3 viewDir = normalize(eyePos - worldPos0);
    vec3 reflectDir = reflect(-direction, norm);  
    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), specularExponent);
    vec3 specular = specularIntensity * specularFactor * base.color;  
        
    vec3 result = diffuse + specular;
    return vec4(result,1.0);
}

vec4 CalcPointLight(PointLight pointLight){
	vec3 lightDir = worldPos0 - pointLight.position;
	float distanceToLight = length(lightDir);

	if(distanceToLight > pointLight.range)
		return vec4(0,0,0,0);
	lightDir = normalize(lightDir);
	vec4 color = CalcLight(pointLight.base, lightDir);

	float attenuation = 1 / (pointLight.attenuation.exponent * distanceToLight * distanceToLight +
						pointLight.attenuation.linear * distanceToLight +
						pointLight.attenuation.constant + 0.00001); 
						// +0.00001 to prevent division with 0

	return color * attenuation;
}

vec4 CalcSpotLight(SpotLight spotLight){
	vec3 lightDir = normalize(worldPos0 - spotLight.pointLight.position);
	float angle = dot(lightDir, normalize(spotLight.direction));
	if(angle > spotLight.cutoff){
		return CalcPointLight(spotLight.pointLight) * (1.0 -(1.0 - angle) / (1.0 - spotLight.cutoff));
	}
	else
		return vec4(0,0,0,0);
}

void main()
{
	fragColor = CalcSpotLight(spotLight) * texture(sampler, textCoord0.xy);
} 