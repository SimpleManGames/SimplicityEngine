#version 450

in vec4 vPosition;
in vec2 vUV;

out vec4 outColor;

layout(location = 0)uniform sampler2D diffuse;
layout(location = 1)uniform sampler2D normal;
layout(location = 2)uniform sampler2D spec;

void main() { 
	outColor = texture(diffuse, vUV) + texture(normal, vUV) + texture(spec, vUV);
}