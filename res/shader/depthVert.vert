#version 430

layout(location = 0)in vec4 position;
layout(location = 3)in vec2 uv;

out vec2 UV;

void main() {
	UV = uv;
	gl_Position = position;
}