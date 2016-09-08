#ifndef _RECT2D_H
#define _RECT2D_H

#ifndef _VECTOR2D_H
#include "Vector2D.h"
#endif

//------------------------------------------------------------------------------
// Rect2D Struct
//------------------------------------------------------------------------------
struct Rect2D {
public:
	Rect2D()
		: left( 0 )
		, top( 0 )
		, right( 0 )
		, bottom( 0 ) {
		width = right - left;
		height = bottom - top;
	}
	Rect2D( const Rect2D& r )
		: left( r.left )
		, top( r.top )
		, right( r.right )
		, bottom( r.bottom ) {
		width = r.width;
		height = r.height;
	}
	Rect2D( double l, double t, double r, double b )
		: left( l )
		, top( t )
		, right( r )
		, bottom( b ) {
		width = right - left;
		height = bottom - top;
	}

	Rect2D( const Vector2D& v1, const Vector2D& v2 )
		: top( v1.y )
		, left( v1.x )
		, bottom( v2.y )
		, right( v2.x ) {
		width = right - left;
		height = bottom - top;
	}
	~Rect2D() {}

	double top;
	double left;
	double bottom;
	double right;

	double width;
	double height;

	static const Rect2D empty;

	Rect2D operator= ( const Rect2D other ) {
		Rect2D r;

		r.left = other.left;
		r.right = other.right;
		r.bottom = other.bottom;
		r.top = other.top;

		r.width = other.width;
		r.height = other.height;

		return r;
	}

	bool operator== ( const Rect2D& other ) {
		if( this->left == other.left && this->right == other.right && this->top == other.top && this->bottom == other.bottom )
			return true;

		return false;
	}

	bool IsEqual( Rect2D& other ) {
		if( this->left == other.left && this->right == other.right && this->top == other.top && this->bottom == other.bottom )
			return true;

		return false;
	}
};

inline bool operator== ( const Rect2D r1, const Rect2D& r2 ) {
	return ( r1.left == r2.left && r1.right == r2.right && r1.top == r2.top && r1.bottom == r2.bottom );
}
inline bool operator!= ( const Rect2D r1, const Rect2D& r2 ) {
	return !( r1 == r2 );
}

#endif

