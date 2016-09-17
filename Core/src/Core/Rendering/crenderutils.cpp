#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#include <cstdio>
#include "Core\Rendering\crenderutils.h"
#include "Helpers\Singleton.h"
#include "Diagnostics\Logger.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "../include/OBJ/tiny_obj_loader.h"
#include "Helpers\FileReader.h"
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
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );
	glEnableVertexAttribArray( 3 );

	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void * )Vertex::POSITION );
	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void * )Vertex::COLOR );
	glVertexAttribPointer( 2, 4, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void * )Vertex::NORMAL );
	glVertexAttribPointer( 3, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void * )Vertex::UV );

	glBindVertexArray( 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	retVal.size = tsize;
	return retVal;
}
Geometry LoadGeometry( const char * path ) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj( &attrib, &shapes, &materials, &err, path );
	
	if( !ret ) {
		Singleton<Logger>::GetInstance().Log( _T( "tinyobj::LoadObj returned false\n Check the file format" ), LOGTYPE_ERROR );
		return{ 0, 0, 0, 0 };
	}

	Geometry retVal;

	for( int s = 0; s < shapes.size(); s++ ) {
		int vSize = shapes[ s ].mesh.indices.size();

		Vertex * verts = new Vertex[ vSize ];
		unsigned * tris = new unsigned[ vSize ];

		for( int i = 0; i < vSize; i++ ) {
			auto ind = shapes[ s ].mesh.indices[ i ];

			const float * n = &attrib.normals[ ind.normal_index * 3 ];
			const float * p = &attrib.vertices[ ind.vertex_index * 3 ];

			verts[ i ].position = glm::vec4( p[ 0 ], p[ 1 ], p[ 2 ], 1.0f );
			verts[ i ].normal = glm::vec4( n[ 0 ], n[ 1 ], n[ 2 ], 0.0f );

			if( ind.texcoord_index >= 0 ) {
				const float * t = &attrib.texcoords[ ind.texcoord_index * 2 ];
				verts[ i ].uv = glm::vec2( t[ 0 ], t[ 1 ] );
			}
			tris[ i ] = i;
		}
		retVal = MakeGeometry( verts, vSize, tris, vSize );

		delete[ ] verts;
		delete[ ] tris;
	}

	return retVal;
}
void FreeGeometry( Geometry & geo ) {
	glDeleteBuffers( 1, &geo.ibo );
	glDeleteBuffers( 1, &geo.vbo );
	glDeleteBuffers( 1, &geo.vao );

	geo = { 0, 0, 0, 0 };
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
Shader LoadShader( const std::tstring & vPath, const std::tstring & fPath ) {
	char * vSource = GetStringFromFile( vPath );
}
void FreeShader( Shader & s ) {
	glDeleteProgram( s.handle );
	s = { 0 };
}

Texture MakeTexture( unsigned width, unsigned height, unsigned format, const unsigned char * pixels ) {
	return Texture();
}

Texture MakeTexture( unsigned width, unsigned height, unsigned format, const float * pixels ) {
	return Texture();
}

Texture LoadTexture( const std::tstring & path ) {
	return Texture();
}

void FreeTexture( Texture & t ) {}

Framebuffer MakeFramebuffer( unsigned width, unsigned height, unsigned nColors ) {
	return Framebuffer();
}

void FreeFramebuffer( Framebuffer & b ) {}

void ClearFramebuffer( const Framebuffer & b ) {}
