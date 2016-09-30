#include "SceneGraph\Component\RenderComponent.h"

RenderComponent::RenderComponent( Geometry g, Shader s, Framebuffer f )
	: geometry( g ), shader( s ), frame( f ) {}

RenderComponent::~RenderComponent() {}

bool RenderComponent::Initialize() {
	return true;
}

void RenderComponent::Draw() {
	Draw_Internal::BeginDraw( shader, geometry, frame );
	Draw_Internal::EndDraw( shader, geometry, frame );
}

void RenderComponent::Update() {}

bool RenderComponent::Shutdown() {
	Geometry_Internal::Free( geometry );
	Shader_Internal::Free( shader );
	Framebuffer_Internal::Free( frame );

	return true;
}