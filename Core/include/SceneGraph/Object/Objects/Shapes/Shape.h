#ifndef _SHAPE_H
#define _SHAPE_H

class Renderer;

#ifndef _COLOR_H
#include "Defines/color.h"
#endif

class Shape {
public:
	Shape();
	virtual ~Shape();

	virtual void Render( Renderer* renderer ) = 0;

	void SetColor( const Color& c );
	const Color& GetColor() const;
private:
	Color color;
};

#endif