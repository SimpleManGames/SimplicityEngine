#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include <cstdio>
#include "Core\Rendering\crenderutils.h"

// Geometry Functions
// ------------------

Geometry MakeGeometry( const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize ) {
	Geometry retVal;

	retVal.size = tsize;
	glGenBuffers( 1, &retVal.vbo );
	glGenBuffers( 1, &retVal.ibo );
	glGenVertexArrays( 1, &retVal.vao );

	glBindVertexArray( retVal.vao );
	glBindBuffer( GL_ARRAY_BUFFER, retVal.vbo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, retVal.ibo );

	glBufferData( GL_ARRAY_BUFFER, vsize * sizeof( Vertex ), verts, GL_STATIC_DRAW );

	glBufferData( GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof( unsigned ), tris, GL_STATIC_DRAW );

	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex ), 0 );

	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

	return retVal;
}
void FreeGeometry( Geometry & geo ) {
	glDeleteBuffers( 1, &geo.ibo );
	glDeleteBuffers( 1, &geo.vbo );
	glDeleteBuffers( 1, &geo.vao );

	geo = { 0,0,0,0 };
}

Shader MakeShader( const char * vert, const char * frag ) {
	Shader retVal;

	retVal.handle = glCreateProgram();
	unsigned vs = glCreateShader( GL_VERTEX_SHADER );
	unsigned fs = glCreateShader( GL_FRAGMENT_SHADER );

	glShaderSource( vs, 1, &vert, NULL );
	glShaderSource( fs, 1, &frag, NULL );

	glCompileShader( vs );
	glCompileShader( fs );

	glAttachShader( retVal.handle, fs );
	glAttachShader( retVal.handle, vs );

	glDeleteShader( vs );
	glDeleteShader( fs );

	return retVal;
}
void FreeShader( Shader & s ) {
	glDeleteProgram( s.handle );
	s = { 0 };
}