#include "Helpers\Math\Vector2D.h"

double Vector2D::Length() const {
	return sqrtf( ( float )x*( float )x + ( float )y*( float )y );
}
double Vector2D::Distance( const Vector2D& vec ) const {
	return sqrtf( ( ( float )vec.x - ( float )x )*( ( float )vec.x - ( float )x ) + ( ( float )vec.y - ( float )y )*( ( float )vec.y - ( float )y ) );
}
Vector2D& Vector2D::Normalize() {
	double xxyy = x*x + y*y;
	double invLength = 1.0 / sqrtf( ( float )xxyy );
	x *= invLength;
	y *= invLength;
	return *this;
}
double Vector2D::Dot( const Vector2D& rhs ) const {
	return ( x*rhs.x + y*rhs.y );
}
Vector2D Vector2D::operator-() const {
	return Vector2D( -x, -y );
}

Vector2D Vector2D::operator+( const Vector2D& rhs ) const {
	return Vector2D( x + rhs.x, y + rhs.y );
}
Vector2D Vector2D::operator-( const Vector2D& rhs ) const {
	return Vector2D( x - rhs.x, y - rhs.y );
}
Vector2D& Vector2D::operator+=( const Vector2D& rhs ) {
	x += rhs.x; y += rhs.y; return *this;
}
Vector2D& Vector2D::operator-=( const Vector2D& rhs ) {
	x -= rhs.x; y -= rhs.y; return *this;
}

Vector2D Vector2D::operator*( const double a ) const {
	return Vector2D( x*a, y*a );
}
Vector2D Vector2D::operator*( const Vector2D& rhs ) const {
	return Vector2D( x*rhs.x, y*rhs.y );
}
Vector2D& Vector2D::operator*=( const double a ) {
	x *= a; y *= a; return *this;
}
Vector2D& Vector2D::operator*=( const Vector2D& rhs ) {
	x *= rhs.x; y *= rhs.y; return *this;
}
Vector2D Vector2D::operator/( const double a ) const {
	return Vector2D( x / a, y / a );
}
Vector2D& Vector2D::operator/=( const double a ) {
	x /= a; y /= a; return *this;
}

bool Vector2D::operator==( const Vector2D& rhs ) const {
	return ( x == rhs.x ) && ( y == rhs.y );
}
bool Vector2D::operator!=( const Vector2D& rhs ) const {
	return ( x != rhs.x ) || ( y != rhs.y );
}

bool Vector2D::operator<( const Vector2D& rhs ) const {
	if( x < rhs.x ) return true;
	if( x > rhs.x ) return false;
	if( y < rhs.y ) return true;
	if( y > rhs.y ) return false;
	return false;
}