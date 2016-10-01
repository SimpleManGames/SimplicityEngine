#include "SceneGraph\Component\RenderComponent.h"

RenderComponent::RenderComponent( Geometry g, Shader s, Framebuffer f ) {}

RenderComponent::~RenderComponent() {}

bool RenderComponent::Initialize() {
	return true;
}

void RenderComponent::Draw() {

}

void RenderComponent::Update() {}

bool RenderComponent::Shutdown() {

	return true;
}