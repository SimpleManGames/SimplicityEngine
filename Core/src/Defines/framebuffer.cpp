#include "Defines\framebuffer.h"

#define GLEW_STATIC
#include "GLEW\glew.h"
#include "STB\stb_image.h"

#include "Defines\geometry.h"

Framebuffer Framebuffer_Internal::Make( unsigned width, unsigned height, unsigned nColors ) {
	Framebuffer retVal = { 0, width, height, nColors };

	glGenFramebuffers( 1, &retVal.handle );
	glBindFramebuffer( GL_FRAMEBUFFER, retVal.handle );

	retVal.depth = Texture_Internal::Make( width, height, GL_DEPTH_COMPONENT, 0 );
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
		retVal.colors[ i ] = Texture_Internal::Make( width, height, GL_RGBA, 0 );
		glFramebufferTexture( GL_FRAMEBUFFER, attachments[ i ], retVal.colors[ i ].handle, 0 );
	}

	glDrawBuffers( nColors, attachments );
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );

	return retVal;
}

void Framebuffer_Internal::Free( Framebuffer & b ) {
	for( unsigned int i = 0; i < b.nColors; ++i ) {
		Texture_Internal::Free( b.colors[ i ] );
	}
	glDeleteFramebuffers( 1, &b.handle );
	b = { 0, 0, 0, 0 };
}

void Framebuffer_Internal::Clear( const Framebuffer & b ) {
	glBindFramebuffer( GL_FRAMEBUFFER, b.handle );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}