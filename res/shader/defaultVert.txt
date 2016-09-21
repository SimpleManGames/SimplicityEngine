#version 450

layout(location = 0)in vec4 position;
layout(location = 3)in vec2 uv;

out vec4 vPosition;
out vec2 vUV;

void main() { 
	vPosition = position;
	vUV = uv;
	gl_Position = position;
}