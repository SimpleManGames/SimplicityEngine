#include "Core\Rendering\Base\TextureBase.h"

#include "GLEW\glew.h"

TextureBase::TextureBase( int textureType )
	: textureType( textureType ), mipMapping( true ), textureId( 0 ) {}

TextureBase::~TextureBase() {}

void TextureBase::Bind() {
	glBindTexture( textureType, textureId );
}

void TextureBase::Unbind() {
	glBindTexture( textureType, 0 );
}

void TextureBase::Unload() {
	if( textureId != 0 ) {
		Unbind();
		glDeleteTextures( 1, &textureId );
		textureId = 0;
	}
}
