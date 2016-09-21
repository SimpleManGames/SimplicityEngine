#include "Core\Rendering\crenderutils.h"

#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJ\tiny_obj_loader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"

#include <cstdio>

#include "Helpers\Singleton.h"
#include "Diagnostics\Logger.h"
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

	for( size_t s = 0; s < shapes.size(); s++ ) {
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
Shader LoadShader( const char * vPath, const char * fPath ) {
	char * v = GetStringFromFile( vPath );
	char * f = GetStringFromFile( fPath );

	if( v == nullptr ) {
		Singleton<Logger>::GetInstance().Log( _T( "Failed to load vertex shader" ), LOGTYPE_ERROR );
		return Shader();
	}

	if( f == nullptr ) {
		Singleton<Logger>::GetInstance().Log( _T( "Failed to load fragment shader" ), LOGTYPE_ERROR );
		return Shader();
	}

	return MakeShader( v, f );
}

void FreeShader( Shader & s ) {
	glDeleteProgram( s.handle );
	s = { 0 };
}

Texture MakeTexture( unsigned width, unsigned height, unsigned format, const unsigned char * pixels ) {
	Texture retVal = { 0, width, height, format };

	glGenTextures( 1, &retVal.handle );
	glBindTexture( GL_TEXTURE_2D, retVal.handle );
	glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glBindTexture( GL_TEXTURE_2D, 0 );

	return retVal;
}

Texture LoadTexture( const char * path ) {
	Texture retVal = { 0, 0, 0, 0 };

	stbi_set_flip_vertically_on_load( true );

	int w, h, f;
	unsigned char * p;

	if( !( p = stbi_load( path, &w, &h, &f, STBI_default ) ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "stbi_load failed to load the texture" ), LOGTYPE_ERROR );
		return retVal;
	}

	switch( f ) {
		case STBI_grey: f = GL_RED; break;
		case STBI_grey_alpha: f = GL_RG; break;
		case STBI_rgb: f = GL_RGB; break;
		case STBI_rgb_alpha: f = GL_RGBA; break;
	}
	retVal = MakeTexture( w, h, f, p );
	stbi_image_free( p );
	return retVal;
}

void FreeTexture( Texture & t ) {
	glDeleteTextures( 1, &t.handle );
	t = { 0,0,0,0 };
}

Framebuffer MakeFramebuffer( unsigned width, unsigned height, unsigned nColors ) {
	Framebuffer retVal = { 0, width, height, nColors };

	glGenFramebuffers( 1, &retVal.handle );
	glBindFramebuffer( GL_FRAMEBUFFER, retVal.handle );

	retVal.depth = MakeTexture( width, height, GL_DEPTH_COMPONENT, 0 );
	glFramebufferTexture( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, retVal.depth.handle, 0 );

	const GLenum attachments[ 8 ] = {
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2,
		GL_COLOR_ATTACHMENT3,
		GL_COLOR_ATTACHMENT4,
		GL_COLOR_ATTACHMENT5,
		GL_COLOR_ATTACHMENT6,
		GL_COLOR_ATTACHMENT7
	};

	for( unsigned int i = 0; i < nColors; ++i ) {
		retVal.colors[ i ] = MakeTexture( width, height, GL_RGBA, 0 );
		glFramebufferTexture( GL_FRAMEBUFFER, attachments[ i ], retVal.colors[ i ].handle, 0 );
	}

	glDrawBuffers( nColors, attachments );
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	return retVal;
}

void FreeFramebuffer( Framebuffer & b ) {
	for( unsigned int i = 0; i < b.nColors; ++i ) {
		FreeTexture( b.colors[ i ] );
	}
	glDeleteFramebuffers( 1, &b.handle );
	b = { 0,0,0,0 };
}

void ClearFramebuffer( const Framebuffer & b ) {
	glBindFramebuffer( GL_FRAMEBUFFER, b.handle );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}