#ifndef _RENDERER_H
#define _RENDERER_H

// Inheiritance Headers
// --------------------

#include "Helpers/Manager.h"

// C Runtime Headers
// -----------------

#ifndef _WINDOWS_H
#include <Windows.h>
#endif // !_WINDOWS_H
#ifndef _VECTOR_
#include <vector>
#endif // !_VECTOR_

// Additional include files
// ------------------------

#ifndef _SHADER_H
#include "Core\Rendering\Shader.h"
#endif // !_SHADER_H
#ifndef _GEOMETRY_H
#include "Defines\geometry.h"
#endif // !_GEOMETRY_H
#ifndef _FRAMEBUFFER_H
#include "Defines\framebuffer.h"
#endif // !_FRAMEBUFFER_H
#ifndef _TEXTURE_H
#include "Defines\texture.h"
#endif // !_FRAMEBUFFER_H

#include "GLM\ext.hpp"

#ifndef _COLOR_H
#include "Defines/color.h"
#endif // !_COLOR_H

// Pre-defined classes
// -------------------

class Graphics;

class Renderer : Manager {
public:
	// Default constructor
	Renderer();
	// Default deconstructor
	~Renderer();
	// Virtual Initialize function inheirited from the Manager class
	virtual bool Initialize();
	// Virtual Shutdown function inheirited from the Manager class
	virtual bool Shutdown();

private:
	// Holds a pointer to the graphics class
	Graphics* graphics;
};

#endif // _RENDERER_H