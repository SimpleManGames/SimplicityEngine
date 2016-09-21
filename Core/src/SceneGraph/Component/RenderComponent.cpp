#include "SceneGraph\Component\RenderComponent.h"

#include "SceneGraph\Object\GameObjects\GameObject.h"
#include "SceneGraph\Scene\Scene.h"

#include "Core\Rendering\Renderer.h"

RenderComponent::RenderComponent( Geometry g, Shader s, Framebuffer f ) {
	geometry = g;
	shader = s;
	frame = f;
}

RenderComponent::~RenderComponent() {}

bool RenderComponent::Initialize() {
	return true;
}

void RenderComponent::Draw() {
	GetParent()->GetScene()->GetRenderer()->Draw(shader, geometry, frame);
}

void RenderComponent::Update() {}

bool RenderComponent::Shutdown() {
	return true;
}
