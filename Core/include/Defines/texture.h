#ifndef _TEXTURE_H
#define _TEXTURE_H

struct Texture {
	unsigned handle;
	unsigned width, height, format;

	template<typename T>
	operator T() { return T(); }
};

namespace Texture_Internal {
	Texture Make( unsigned width, unsigned height, unsigned format, const unsigned char * pixels );
	Texture Load( const char * path );
	void Free( Texture &t );
}

#endif // !_TEXTURE_H