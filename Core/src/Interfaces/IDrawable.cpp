#include "Interfaces/IDrawable.h"

IDrawable::IDrawable()
	:canDraw( true ) {}
IDrawable::~IDrawable() {}

void IDrawable::SetCanDraw( bool Draw ) {
	this->canDraw = Draw;
}
bool IDrawable::GetCanDraw() const {
	return this->canDraw;
}