#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include "texture.h"

struct Framebuffer {
	unsigned handle;
	unsigned width, height;
	unsigned nColors;
	Texture depth;
	Texture colors[ 8 ];

	template<typename T>
	operator T() { return T(); }
};

namespace Framebuffer_Internal {
	Framebuffer Make( unsigned width, unsigned height, unsigned nColors );
	void Free( Framebuffer & b );
	void Clear( const Framebuffer & b );
}

#endif // !_FRAMEBUFFER_H