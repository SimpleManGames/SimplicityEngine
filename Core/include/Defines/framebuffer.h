#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include "Defines\texture.h"

struct Framebuffer {
	unsigned handle;
	unsigned width, height;
	unsigned nColors;
	Texture colors[ 8 ];
};

#endif // !_FRAMEBUFFER_H