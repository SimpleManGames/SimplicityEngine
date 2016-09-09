#ifndef _CRENDERUTILS_H
#define _CRENDERUTILS_H

#include "Defines\geometry.h"
#include "Defines\vertex.h"
#include "Defines\shader.h"

Geometry MakeGeometry( const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize );
void FreeGeometry( Geometry & geo );

Shader MakeShader( const char * vert, const char * frag );
void FreeShader( Shader & s );

#endif // !_CRENDERUTILS_H