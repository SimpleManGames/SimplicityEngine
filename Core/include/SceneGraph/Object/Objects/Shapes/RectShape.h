#ifndef _RECTSHAPE_H
#define _RECTSHAPE_H

#include "SceneGraph/Object/Objects/Shapes/Shape.h"
#include "Interfaces/IFillableShape.h"

#ifndef _VECTOR2D_H
#include "Helpers/Math/Vector2D.h"
#endif
#ifndef _RECT2D_H
#include "Helpers/Math/Rect2D.h"
#endif

class Renderer;

class RectShape : public Shape, public IFillableShape {
public:
	RectShape( double left, double top, double width, double height, float lineWidth = 0.5f );
	RectShape( const Vector2D& lefttop, const Vector2D& rightbottom, float lineWidth = 0.5f );
	RectShape( const Rect2D& rect, float lineWidth = 0.5f );
	virtual ~RectShape();

	virtual void SetFill( bool fill );
	virtual bool GetFill() const;

	virtual void Render( Renderer* renderer );

private:
	Rect2D rect;
	float lineWidth;
};

#endif