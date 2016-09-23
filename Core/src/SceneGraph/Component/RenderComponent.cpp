#include "SceneGraph\Component\RenderComponent.h"

RenderComponent::RenderComponent( Geometry g, Shader s, Framebuffer f ) {
	geometry = g;
	shader = s;
	frame = f;
}
RenderComponent::~RenderComponent() {  }

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
