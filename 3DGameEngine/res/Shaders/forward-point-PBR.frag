#version 330

out vec4 FragColor;

in vec3 worldPos0;
in vec2 textCoord0;
in mat3 TBN0;

uniform vec3 eyePos;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;

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

uniform PointLight pointLight;

uniform vec3 color;

const float PI = 3.14159265359;

vec3 GetNormalFromMap(){
	vec3 normal = texture(normalMap, textCoord0).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(TBN0 * normal);
	return normal;
}

//calculate ratio between specular and diffuse
vec3 FresnelSchlick(float cosHalfView, vec3 F0){
	return F0 + (1.0 - F0) * pow(1.0 - cosHalfView, 5.0);
}

//approximate ratio of microfacets aligned to the halfway vector
float DistributionGGX(vec3 normal, vec3 halfway, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(normal, halfway), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float normalDotView, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = normalDotView;
    float denom = normalDotView * (1.0 - k) + k;
	
    return num / denom;
}

//approximate the ratio of microfacets that overshadow each other
float GeometrySmith(vec3 normal, vec3 viewDir, vec3 lightDir, float roughness)
{
    float NdotV = max(dot(normal, viewDir), 0.0);
    float NdotL = max(dot(normal, lightDir), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

void main(){
	vec3 albedo     = pow(texture(albedoMap, textCoord0).rgb, vec3(2.2));
	vec3 normal = GetNormalFromMap();
    float metallic  = texture(metallicMap, textCoord0).r;
    float roughness = texture(roughnessMap, textCoord0).r;
    float ao        = texture(aoMap, textCoord0).r;

    vec3 viewDir = normalize(eyePos - worldPos0);

    vec3 lightDir = pointLight.position - worldPos0;
    float distanceToLight = length(lightDir);

    
    lightDir = normalize(lightDir);
    vec3 halfVector = normalize(lightDir + viewDir);

    vec3 F0 = vec3(0.04); //this is good for every non-metallic
	F0      = mix(F0, albedo, metallic);

	//Cook-Torrance BRDF
    float NDF = DistributionGGX(normal, halfVector, roughness);   
    float G   = GeometrySmith(normal, viewDir, lightDir, roughness);      
    vec3 F    = FresnelSchlick(max(dot(halfVector, viewDir), 0.0), F0);
    vec3 numerator    = NDF * G * F;
	float denominator = 4.0 * max(dot(normal, viewDir), 0.0) * max(dot(normal, lightDir), 0.0);
	vec3 specular     = numerator / max(denominator, 0.00001);  

	vec3 specularRatio = F;
	vec3 diffuse = vec3(1.0) - specularRatio;

	//metallic surfaces have no diffuse so we nullify it if metallic = 1
	diffuse *= 1.0 - metallic;

 	// scale light by NdotL
    float angle = max(dot(normal, lightDir), 0.0);        

    // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    vec3 outRadiance = (diffuse * albedo * color / PI + specular) * pointLight.base.color * angle;  

    float attenuation = 1 / (pointLight.attenuation.exponent * distanceToLight * distanceToLight +
                        pointLight.attenuation.linear * distanceToLight +
                        pointLight.attenuation.constant + 0.00001); 
                        // +0.00001 to prevent division with 0

    outRadiance = outRadiance * attenuation;

    vec3 colorOut = outRadiance / (outRadiance + vec3(1.0));
    colorOut = pow(colorOut, vec3(1.0/2.2));  
    if(distanceToLight > pointLight.range)
        FragColor = vec4(0,0,0,0);
    else
        FragColor = vec4(colorOut, 1.0);

}