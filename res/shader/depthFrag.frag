#version 430

in vec2 UV;

layout(location = 0)uniform mat4 proj;
layout(location = 1)uniform mat4 view;
layout(location = 2)uniform mat4 model;

layout(location = 3)uniform sampler2D colorMap;
layout(location = 4)uniform sampler2D diffuseMap;
layout(location = 5)uniform sampler2D specMap;
layout(location = 6)uniform sampler2D depth;

uniform vec2 sDim = vec2(1280, 720);
uniform float focus;

uniform float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
uniform float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

out vec4 outColor;


void main()
{
	
	outColor = texture2D(colorMap, UV / textureSize(colorMap, 0).x) * weight[0];
	for(int i = 0; i < 1; i++) {
		outColor += texture2D(colorMap, ( UV + vec2(0.0, offset[i]) ) / textureSize(colorMap, 0).x) * weight[i];
		outColor += texture2D(colorMap, ( UV - vec2(0.0, offset[i]) ) / textureSize(colorMap, 0).x) * weight[i];
	}
	
}