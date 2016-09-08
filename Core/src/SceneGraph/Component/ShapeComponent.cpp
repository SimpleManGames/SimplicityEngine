#include "SceneGraph/Component/ShapeComponent.h"

#include "SceneGraph/Object/Objects/Shapes/Shape.h"
#include "SceneGraph/Object/GameObjects/GameObject.h"
#include "SceneGraph/Scene/Scene.h"

#include "Core/Rendering/Renderer.h"

#include "Interfaces/IFillableShape.h"

#include "Defines/deletemacros.h"

ShapeComponent::ShapeComponent( Shape* shape )
	:shape( shape ) {}
ShapeComponent::~ShapeComponent() {
	SafeDelete( this->shape );
}

bool ShapeComponent::Initialize() {
	return true;
}
void ShapeComponent::Draw() {
	this->shape->Render( GetParent()->GetScene()->GetRenderer() );
}
void ShapeComponent::Update() {

}
bool ShapeComponent::Shutdown() {
	return true;
}

void ShapeComponent::SetFill( bool fill ) {
	IFillableShape* fillable = dynamic_cast< IFillableShape* >( this->shape );
	if( fillable )
		fillable->SetFill( fill );
}
bool ShapeComponent::GetFill() const {
	IFillableShape* fillable = dynamic_cast< IFillableShape* >( this->shape );
	if( fillable )
		return fillable->GetFill();

	return false;
}

void ShapeComponent::SetColor( const Color& c ) {
	this->shape->SetColor( c );
}
const Color& ShapeComponent::GetColor() const {
	return this->shape->GetColor();
}