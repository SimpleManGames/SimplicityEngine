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
#include "Defines\shader.h"
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

namespace Draw_Internal {
	void BeginDraw( const Shader &s, const Geometry &g, const Framebuffer &r );
	void EndDraw( const Shader &s, const Geometry &g, const Framebuffer &r );

	size_t Format( size_t idx, size_t tex, int val );
	size_t Format( size_t idx, size_t tex, float val );
	size_t Format( size_t idx, size_t tex, const Texture & val );
	size_t Format( size_t idx, size_t tex, const glm::vec3 & val );
	size_t Format( size_t idx, size_t tex, const glm::mat4 & val );
	size_t Format( size_t idx, size_t tex, const float val[ 16 ] );

	template<typename T, typename ...U>
	void Unpack( size_t idx, size_t tex, T val, U &&...uniforms ) {
		tex += Format( idx, tex, val );
		Unpack( idx + 1, tex, uniforms... );
	}

	template<typename T>
	void Unpack( size_t idx, size_t tex, T val ) {
		Format( idx, tex, val );
	}

}

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

	template<typename ...U>
	inline void Draw( const Shader &s, const Geometry &g, const Framebuffer &r, U ... uniforms ) {
		Draw_Internal::BeginDraw( s, g, r );
		Draw_Internal::Unpack( 0, 0, uniforms... );
		Draw_Internal::EndDraw( s, g, r );
	}
	inline void Draw( const Shader &s, const Geometry &g, const Framebuffer &r ) {
		Draw_Internal::BeginDraw( s, g, r );
		Draw_Internal::EndDraw( s, g, r );
	}

private:
	// Holds a pointer to the graphics class
	Graphics* graphics;
};

#endif // _RENDERER_H