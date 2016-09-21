#version 430

in vec2 UV;

layout(location = 0)uniform mat4 proj;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

layout(location = 3)uniform sampler2D colorMap;
layout(location = 4)uniform sampler2D diffuseMap;
layout(location = 5)uniform sampler2D specMap;
layout(location = 6)uniform sampler2D depth;

out vec4 outColor;

uniform vec2 sDim = vec2(1280, 720);

void main()
{
	vec4 xSColor = 
	texture(specMap, UV + vec2( -1, -1) / sDim)     +
	texture(specMap, UV + vec2( -1,  0) / sDim) * 2 +
	texture(specMap, UV + vec2( -1,  1) / sDim) -
	texture(specMap, UV + vec2(  1, -1) / sDim) -
	texture(specMap, UV + vec2(  1,  0) / sDim) * 2 -
	texture(specMap, UV + vec2(  1,  1) / sDim);
	
	vec4 ySColor = 
	texture(specMap, UV + vec2( 1, -1) / sDim) +
	texture(specMap, UV + vec2( 0, -1) / sDim) * 2 +
	texture(specMap, UV + vec2(-1, -1) / sDim) -
	texture(specMap, UV + vec2( 1,  1) / sDim) -
	texture(specMap, UV + vec2( 0,  1) / sDim) * 2 -
	texture(specMap, UV + vec2(-1,  1) / sDim);

	vec4 xCColor = 
	texture(colorMap, UV + vec2( -1, -1) / sDim)     +
	texture(colorMap, UV + vec2( -1,  0) / sDim) * 2 +
	texture(colorMap, UV + vec2( -1,  1) / sDim) -
	texture(colorMap, UV + vec2(  1, -1) / sDim) -
	texture(colorMap, UV + vec2(  1,  0) / sDim) * 2 -
	texture(colorMap, UV + vec2(  1,  1) / sDim);

	vec4 yCColor = 
	texture(colorMap, UV + vec2( 1, -1) / sDim) +
	texture(colorMap, UV + vec2( 0, -1) / sDim) * 2 +
	texture(colorMap, UV + vec2(-1, -1) / sDim) -
	texture(colorMap, UV + vec2( 1,  1) / sDim) -
	texture(colorMap, UV + vec2( 0,  1) / sDim) * 2 -
	texture(colorMap, UV + vec2(-1,  1) / sDim);
	
	outColor = sqrt(xCColor * xCColor + yCColor * yCColor);
}