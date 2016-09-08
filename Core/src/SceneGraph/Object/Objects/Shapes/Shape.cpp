#include "SceneGraph/Object/Objects/Shapes/Shape.h"

Shape::Shape()
	:color( 1, 1, 1, 1 ) {}
Shape::~Shape() {}

void Shape::SetColor( const Color& c ) {
	this->color = c;
}
const Color& Shape::GetColor() const {
	return this->color;
}