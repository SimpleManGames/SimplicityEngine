#include "Defines\geometry.h"

#define GLEW_STATIC
#include "glew\glew.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "OBJ\tiny_obj_loader.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

#include "Helpers\Singleton.h"
#include "Diagnostics\Logger.h"


Geometry Geometry_Internal::Make( const Vertex * verts, size_t vsize, const unsigned * tris, size_t tsize ) {
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

Geometry Geometry_Internal::Load( const char * path ) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj( &attrib, &shapes, &materials, &err, path );

	Geometry retVal = { 0, 0, 0, 0 };

	if( !ret ) {
		Singleton<Logger>::GetInstance().Log( _T( "tinyobj Failed to load requested model from file. \n Check path or file format" ), LOGTYPE_WARNING );
		return retVal;
	}

	for( unsigned int s = 0; s < shapes.size(); s++ ) {
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
		retVal = Geometry_Internal::Make( verts, vSize, tris, vSize );

		delete[ ] verts;
		delete[ ] tris;
	}

	return retVal;
}

void Geometry_Internal::Free( Geometry & g ) {
	glDeleteBuffers( 1, &g.vbo );
	glDeleteBuffers( 1, &g.ibo );
	glDeleteVertexArrays( 1, &g.vao );
	g = { 0, 0, 0, 0 };
}
