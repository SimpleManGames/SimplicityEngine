#ifndef _POLYGONSHAPE_H
#define _POLYGONSHAPE_H

#include "SceneGraph/Object/Objects/Shapes/Shape.h"
#include "Interfaces/IFillableShape.h"

#ifndef _VECTOR2D_H
#include "Helpers/Math/Vector2D.h"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

class Renderer;

class PolygonShape : public Shape, public IFillableShape {
public:
	PolygonShape( Vector2D* points, int size, bool close = true, float lineWidth = 0.5f );
	PolygonShape( const std::vector<Vector2D>& vecPoints, bool close = true, float lineWidth = 0.5f );
	virtual ~PolygonShape();

	virtual void SetFill( bool fill );
	virtual bool GetFill() const;

	virtual void Render( Renderer* renderer );
private:
	std::vector<Vector2D> points;
	bool close;
	float lineWidth;
};

#endif