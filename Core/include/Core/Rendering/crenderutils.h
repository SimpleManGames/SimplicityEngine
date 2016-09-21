#ifndef _CRENDERUTILS_H
#define _CRENDERUTILS_H

#include "Defines\geometry.h"
#include "Defines\vertex.h"
#include "Defines\shader.h"
#include "Defines\texture.h"
#include "Defines\framebuffer.h"

#include "Defines\string.h"

Geometry MakeGeometry( const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize );
Geometry LoadGeometry( const char * path );
void FreeGeometry( Geometry & geo );

Shader MakeShader( const char * vert, const char * frag );
Shader LoadShader( const std::tstring & vPath, const std::tstring & fPath );
void FreeShader( Shader & s );

Texture MakeTexture( unsigned width, unsigned height, unsigned format, const unsigned char * pixels );
Texture LoadTexture( const std::tstring & path );
void FreeTexture( Texture & t );

Framebuffer MakeFramebuffer( unsigned width, unsigned height, unsigned nColors );
void FreeFramebuffer( Framebuffer & b );
void ClearFramebuffer( const Framebuffer & b );

#endif // !_CRENDERUTILS_H