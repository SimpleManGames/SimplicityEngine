#ifndef _RENDERCOMPONENT_H
#define _RENDERCOMPONENT_H

#include "SceneGraph\Component\Component.h"
#include "Interfaces\IDrawable.h"

#include "Defines\geometry.h"
#include "Defines\shader.h"
#include "Defines\framebuffer.h"

class RenderComponent : public Component, public IDrawable {
public:
	RenderComponent( Geometry g, Shader s, Framebuffer f );
	virtual ~RenderComponent();

	virtual bool Initialize();
	virtual void Draw();
	virtual void Update();
	virtual bool Shutdown();

private:
	Geometry geometry;
	Shader shader;
	Framebuffer frame;
};

#endif // !_RENDERCOMPONENT_H