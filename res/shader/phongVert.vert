#version 430

layout(location = 0) in vec4 position;
layout(location = 2) in vec4 normal;
layout(location = 3) in vec2 texcoord;

layout(location = 0)uniform mat4 proj;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

out vec3 vPosition;
out vec3 vNormal;
out vec2 UV;

void main()
{
	vPosition = (model * position).xyz;
	vNormal   = normalize(model * normal).xyz;

	UV = texcoord;		
	gl_Position = proj * view * model * position;
}