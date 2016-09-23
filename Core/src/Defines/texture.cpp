#include "Defines\texture.h"

#define GLEW_STATIC
#include "GLEW\glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB\stb_image.h"

#include "Diagnostics\Logger.h"
#include "Helpers\Singleton.h"

Texture Texture_Internal::Make( unsigned width, unsigned height, unsigned format, const unsigned char * pixels ) {
	Texture retval = { 0, width, height, format };

	glGenTextures( 1, &retval.handle );
	glBindTexture( GL_TEXTURE_2D, retval.handle );
	glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glBindTexture( GL_TEXTURE_2D, 0 );

	return retval;
}

Texture Texture_Internal::Load( const char * path ) {
	Texture retval = { 0, 0, 0, 0 };

	stbi_set_flip_vertically_on_load( true );

	int w, h, f;
	unsigned char * p;

	p = stbi_load( path, &w, &h, &f, STBI_default );

	if( !p ) {
		Singleton<Logger>::GetInstance().Log( _T( "Failed to load file" ), LOGTYPE_ERROR );
		return retval;
	}

	switch( f ) {
		case STBI_grey: f = GL_RED; break;
		case STBI_grey_alpha: f = GL_RG; break;
		case STBI_rgb: f = GL_RGB; break;
		case STBI_rgb_alpha: f = GL_RGBA; break;
	}
	retval = Texture_Internal::Make( w, h, f, p );
	stbi_image_free( p );
	return retval;
}

void Texture_Internal::Free( Texture & t ) {
	glDeleteTextures( 1, &t.handle );
	t = { 0, 0, 0, 0 };
}
