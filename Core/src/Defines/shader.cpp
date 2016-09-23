#include "Defines\shader.h"

#define GLEW_STATIC
#include "GLEW\glew.h"

#ifndef _FILEREADER_H
#include "Helpers\FileReader.h"
#endif // !_FILEREADER_H

Shader Shader_Internal::Make( const char * vert, const char * frag ) {
	// Create varibles
	Shader retval;

	retval.handle = glCreateProgram();

	unsigned vs = glCreateShader( GL_VERTEX_SHADER );
	unsigned fs = glCreateShader( GL_FRAGMENT_SHADER );

	// Init varibles
	glShaderSource( vs, 1, &vert, 0 );
	glShaderSource( fs, 1, &frag, 0 );

	// Compile shaders
	glCompileShader( vs );
	glCompileShader( fs );

	// Link the shaders to one program
	glAttachShader( retval.handle, vs );
	glAttachShader( retval.handle, fs );
	glLinkProgram( retval.handle );

	// Delete the shader, don't need them anymore
	glDeleteShader( vs );
	glDeleteShader( fs );

	// Return the program
	return retval;
}

Shader Shader_Internal::Load( const char * vPath, const char * fPath ) {
	return Make( GetStringFromFile( vPath ), GetStringFromFile( fPath ) );
}

void Shader_Internal::Free( Shader & s ) {
	glDeleteProgram( s.handle );
	s.handle = 0;
}
