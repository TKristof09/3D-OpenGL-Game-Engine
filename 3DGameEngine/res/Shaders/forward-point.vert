#version 330
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in ivec4 ids;
layout (location = 5) in vec4 weights;

out vec3 worldPos0;
out vec2 textCoord0;
out mat3 TBN0;

uniform mat4 model;
uniform mat4 MVP;

const int MAX_BONES = 100;
uniform mat4 bones[MAX_BONES];
uniform bool animated;

void main(){

	textCoord0 = textCoord;

	mat4 bone_transform;
	if(animated)
	{
		bone_transform = bones[ids[0]] * weights[0];
		bone_transform += bones[ids[1]] * weights[1];
		bone_transform += bones[ids[2]] * weights[2];
		bone_transform += bones[ids[3]] * weights[3];
	}

	worldPos0 = (model * bone_transform * vec4(position, 1.0)).xyz;


	vec3 T = normalize(vec3(model * bone_transform * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(model * bone_transform * vec4(normal, 0.0)));
	// re-orthogonalize T with respect to N
	T = normalize(T - dot(T, N) * N);
	// then retrieve perpendicular vector B with the cross product of T and N
	vec3 B = cross(N, T);
   	TBN0 = mat3(T, B, N);


	gl_Position = MVP * bone_transform * vec4(position, 1.0);
}