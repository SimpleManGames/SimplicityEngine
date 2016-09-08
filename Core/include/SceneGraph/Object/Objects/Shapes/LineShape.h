#ifndef _LINESHAPE_H
#define _LINESHAPE_H

#include "SceneGraph/Object/Objects/Shapes/Shape.h"

#ifndef _VECTOR2D_H
#include "Helpers/Math/Vector2D.h"
#endif

class Renderer;

class LineShape : public Shape
{
public:
	LineShape(float x1, float y1, float x2, float y2, float lineWidth = 0.5f);
	LineShape(const Vector2D& v1, const Vector2D& v2, float lineWidth = 0.5f);
	virtual ~LineShape();

	virtual void Render(Renderer* renderer);
private:
	Vector2D v1;
	Vector2D v2;
	float lineWidth;
};

#endif