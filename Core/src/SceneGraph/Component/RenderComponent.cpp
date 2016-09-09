#include "SceneGraph\Component\RenderComponent.h"

#include "SceneGraph\Object\GameObjects\GameObject.h"
#include "SceneGraph\Scene\Scene.h"

#include "Core\Rendering\Renderer.h"

RenderComponent::RenderComponent( Geometry g, Shader s ) {
	geometry = g;
	shader = s;
}

RenderComponent::~RenderComponent() {}

bool RenderComponent::Initialize() {
	return true;
}

void RenderComponent::Draw() {
	GetParent()->GetScene()->GetRenderer()->DrawModel(shader, geometry);
}

void RenderComponent::Update() {}

bool RenderComponent::Shutdown() {
	return true;
}
