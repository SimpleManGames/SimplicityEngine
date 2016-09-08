#include "SceneGraph/Object/Objects/Shapes/CircleShape.h"

#include "Core/Rendering/Renderer.h"

#include "Defines/assert.h"

CircleShape::CircleShape( float xcenter, float ycenter, float r, float lineWidth )
	:CircleShape( Vector2D( xcenter, ycenter ), r, lineWidth ) {}
CircleShape::CircleShape( const Vector2D& center, float r, float lineWidth )
	: center( center )
	, radius( r )
	, lineWidth( lineWidth ) {}
CircleShape::~CircleShape() {}

void CircleShape::Render( Renderer* renderer ) {
	//Renderer cannot be null
	assert( renderer != nullptr );

	renderer->SetColor( GetColor() );

	GetFill()
		? renderer->FillCircle( this->center, this->radius )
		: renderer->DrawCircle( this->center, this->radius, this->lineWidth );
}

void CircleShape::SetFill( bool fill ) {
	this->fill = fill;
}
bool CircleShape::GetFill() const {
	return this->fill;
}