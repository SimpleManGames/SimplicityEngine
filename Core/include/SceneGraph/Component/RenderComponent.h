#ifndef _RENDERCOMPONENT_H
#define _RENDERCOMPONENT_H

#include "SceneGraph\Object\GameObjects\GameObject.h"
#include "SceneGraph\Scene\Scene.h"

#include "Core\Rendering\Renderer.h"

#include "SceneGraph\Component\Component.h"
#include "Interfaces\IDrawable.h"

#include "Defines\geometry.h"
#include "Defines\shader.h"
#include "Defines\framebuffer.h"
#include "Core\Rendering\Material.h"

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