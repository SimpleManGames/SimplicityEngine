#ifndef _RENDERER_H
#define _RENDERER_H

// Inheiritance Headers
// --------------------

#include "Helpers/Manager.h"

// C Runtime Headers
// -----------------

#ifndef _WINDOWS_H
#include <Windows.h>
#endif // !_WINDOWS_H
#ifndef _VECTOR_
#include <vector>
#endif // !_VECTOR_

// Additional include files
// ------------------------

#ifndef _VECTOR2D_H
#include "Helpers/Math/Vector2D.h"
#endif // !_VECTOR2D_H
#ifndef _MATRIX2D_H
#include "Helpers/Math/Matrix2D.h"
#endif // !_MATRIX2D_H
#ifndef _RECT2D_H
#include "Helpers/Math/Rect2D.h"
#endif // !_RECT2D_H

#ifndef _COLOR_H
#include "Defines/color.h"
#endif // !_COLOR_H

// Pre-defined classes
// -------------------

class Graphics;

class Renderer : Manager {
public:
	// Default constructor
	Renderer();
	// Default deconstructor
	~Renderer();
	// Virtual Initialize function inheirited from the Manager class
	virtual bool Initialize();
	// Virtual Shutdown function inheirited from the Manager class
	virtual bool Shutdown();

	// Set the color that the renderer will use to draw
	void SetColor( const Color& c );
	// Set the color that the renderer will use to draw
	void SetColor( float r, float g, float b, float a = 1.0f );

	// Draw a line between two points
	void DrawLine( const Vector2D& v1, const Vector2D& v2, float lineWidth = 0.5f );
	// Draw a line between two points
	void DrawLine( float x1, float y1, float x2, float y2, float lineWidth = 0.5f );

	// Draw a rectangle at the coords listed
	void DrawRect( double left, double top, double width, double height, float lineWidth = 0.5f );
	// Draw a rectangle at the coords listed
	void DrawRect( const Vector2D& lefttop, const Vector2D& rightbottom, float lineWidth = 0.5f );
	// Draw a rectangle at the coords listed
	void DrawRect( const Rect2D& rect, float lineWidth = 0.5f );

	// Draw a circle at the point and size
	void DrawCircle( double xcenter, double ycenter, double r, float lineWidth = 0.5f );
	// Draw a circle at the point and size
	void DrawCircle( const Vector2D& center, double r, float lineWidth = 0.5f );

	// Draw a polygon at the points
	void DrawPolygon( const std::vector<Vector2D>& vecPoints, bool close = true, float lineWidth = 0.5f );
	// Draw a polygon at the points
	void DrawPolygon( Vector2D* points, int size, bool close = true, float lineWidth = 0.5f );

	// Draw a filled rectangle
	void FillRect( double left, double top, double width, double height );
	// Draw a filled rectangle
	void FillRect( const Vector2D& lefttop, const Vector2D& rightbottom );
	// Draw a filled rectangle
	void FillRect( const Rect2D& rect );

	// Draw a filled circle 
	void FillCircle( const Vector2D& center, double r );
	// Draw a filled circle
	void FillCircle( double xcenter, double ycenter, double r );

	// Draw a filled polygon
	void FillPolygon( const std::vector<Vector2D>& vecPoints );
	// Draw a filled polygon
	void FillPolygon( Vector2D* points, int size );

private:
	// Holds a pointer to the graphics class
	Graphics* graphics;
};

#endif // _RENDERER_H