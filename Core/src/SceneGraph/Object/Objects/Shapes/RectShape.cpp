#include "SceneGraph/Object/Objects/Shapes/RectShape.h"

#include "Core/Rendering/Renderer.h"

#include "Defines/assert.h"

RectShape::RectShape( double left, double top, double width, double height, float lineWidth )
	:RectShape( Rect2D( left, top, left + width, top + height ), lineWidth ) {}
RectShape::RectShape( const Vector2D& lefttop, const Vector2D& rightbottom, float lineWidth )
	: RectShape( Rect2D( lefttop, rightbottom ), lineWidth ) {}
RectShape::RectShape( const Rect2D& rect, float lineWidth )
	: rect( rect )
	, lineWidth( lineWidth ) {}
RectShape::~RectShape() {}

void RectShape::Render( Renderer* renderer ) {
	//Renderer cannot be null
	assert( renderer != nullptr );

	renderer->SetColor( GetColor() );

	GetFill()
		? renderer->FillRect( this->rect )
		: renderer->DrawRect( this->rect, this->lineWidth );
}

void RectShape::SetFill( bool fill ) {
	this->fill = fill;
}
bool RectShape::GetFill() const {
	return this->fill;
}