#ifndef _SHAPECOMPONENT_H
#define _SHAPECOMPONENT_H

#include "SceneGraph/Component/Component.h"
#include "Interfaces/IDrawable.h"

#ifndef _COLOR_H
#include "Defines/color.h"
#endif

class Shape;

class ShapeComponent : public Component, public IDrawable {
public:
	ShapeComponent( Shape* shape );
	virtual ~ShapeComponent();

	virtual bool Initialize();
	virtual void Draw();
	virtual void Update();
	virtual bool Shutdown();

	void SetFill( bool fill );
	bool GetFill() const;

	void SetColor( const Color& c );
	const Color& GetColor() const;

private:
	Shape* shape;
};

#endif