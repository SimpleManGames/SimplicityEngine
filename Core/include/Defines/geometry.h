#ifndef _GEOMETRY_H
#define _GEOMETRY_H

#ifndef _VERTEX_H
#include "Defines\vertex.h"
#endif // !_VERTEX_H

struct Geometry { 
	unsigned vao, vbo, ibo, size;

	template<typename T>
	operator T() { return T(); }
};

namespace Geometry_Internal {
	Geometry Make( const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize );
	Geometry Load( const char * path );
	void Free( Geometry & g );
}

#endif // !_GEOMETRY_H