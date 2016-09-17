#ifndef _VERTEX_H
#define _VERTEX_H

#include "GLM\glm.hpp"

struct Vertex {

	glm::vec4 position;
	glm::vec4 color;
	glm::vec4 normal;
	glm::vec2 uv;

	enum {
		POSITION = 0, 
		COLOR = 16,
		NORMAL = 32,
		UV = 48
	};
};

#endif // !_VERTEX_H