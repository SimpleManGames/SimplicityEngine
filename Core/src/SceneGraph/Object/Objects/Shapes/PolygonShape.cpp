#include "SceneGraph/Object/Objects/Shapes/PolygonShape.h"

#include "Core/Rendering/Renderer.h"

#include "Defines/assert.h"

PolygonShape::PolygonShape( Vector2D* points, int size, bool close, float lineWidth )
	:PolygonShape( std::vector<Vector2D>( points, points + size ), close, lineWidth ) {}
PolygonShape::PolygonShape( const std::vector<Vector2D>& vecPoints, bool close, float lineWidth )
	: points( vecPoints )
	, close( close )
	, lineWidth( lineWidth ) {}
PolygonShape::~PolygonShape() {}

void PolygonShape::Render( Renderer* renderer ) {
	//Renderer cannot be null
	assert( renderer != nullptr );

	renderer->SetColor( GetColor() );

	GetFill()
		? renderer->FillPolygon( this->points )
		: renderer->DrawPolygon( this->points, this->close, this->lineWidth );
}

void PolygonShape::SetFill( bool fill ) {
	this->fill = fill;
}
bool PolygonShape::GetFill() const {
	return this->fill;
}