#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

out vec3 worldPos0;
out vec2 textCoord0;
out mat3 TBN0;

uniform mat4 model;
uniform mat4 MVP;

void main(){
	
	textCoord0 = textCoord;
	worldPos0 = (model * vec4(position, 1.0)).xyz;


	vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(normal, 0.0)));
	// re-orthogonalize T with respect to N
	T = normalize(T - dot(T, N) * N);
	// then retrieve perpendicular vector B with the cross product of T and N
	vec3 B = cross(N, T);
   	TBN0 = mat3(T, B, N);

	gl_Position = MVP * vec4(position, 1.0);
}