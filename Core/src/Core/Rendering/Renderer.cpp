#include "Core/Rendering/Renderer.h"

#include "Core/System/Graphics.h"
#include "Core/System/Manager/SystemManager.h"

#include "GLEW\glew.h"

#include "Diagnostics/Logger.h"

#include "Defines/assert.h"
#include "Defines/deletemacros.h"

#include "Helpers/Singleton.h"

Renderer::Renderer() {}
Renderer::~Renderer() {}

bool Renderer::Initialize() {
	this->graphics = dynamic_cast< Graphics* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::GRAPHICS_SYSTEM ) );
	assert( this->graphics != nullptr );

	return true;
}
bool Renderer::Shutdown() {
	return true;
}

void Renderer::SetColor( const Color& c ) {
	//this->graphics->GetColorBrush()->SetColor( D2D1::ColorF( c.red, c.green, c.blue, c.alpha ) );
}
void Renderer::SetColor( float r, float g, float b, float a ) {
	SetColor( Color( r, g, b, a ) );
}

void Renderer::DrawLine( const Vector2D& v1, const Vector2D& v2, float lineWidth ) {

}
void Renderer::DrawLine( float x1, float y1, float x2, float y2, float lineWidth ) {
	Vector2D v1( x1, y1 );
	Vector2D v2( x2, y2 );

	DrawLine( v1, v2, lineWidth );
}

void Renderer::DrawRect( double left, double top, double width, double height, float lineWidth ) {
	DrawRect( Rect2D( left, top, left + width, top + height ), lineWidth );
}
void Renderer::DrawRect( const Vector2D& lefttop, const Vector2D& rightbottom, float lineWidth ) {
	DrawRect( Rect2D( lefttop, rightbottom ), lineWidth );
}
void Renderer::DrawRect( const Rect2D& rect, float lineWidth ) {

}

void Renderer::DrawCircle( double xcenter, double ycenter, double r, float lineWidth ) {

}
void Renderer::DrawCircle( const Vector2D& center, double r, float lineWidth ) {
	DrawCircle( center.x, center.y, r, lineWidth );
}

void Renderer::DrawPolygon( const std::vector<Vector2D>& vecPoints, bool close, float lineWidth ) {
	Vector2D* points = new Vector2D[ ( int )vecPoints.size() ];
	for( int i = 0; i < ( int )vecPoints.size(); ++i )
		points[ i ] = vecPoints[ i ];

	DrawPolygon( points, vecPoints.size(), close, lineWidth );
}
void Renderer::DrawPolygon( Vector2D* points, int size, bool close, float lineWidth ) {
	//Do not draw an empty polygon
	if( size < 3 )
		return;

	for( int countloop = 0; countloop < size - 1; ++countloop )
		DrawLine( points[ countloop ], points[ countloop + 1 ], lineWidth );

	if( close )
		DrawLine( points[ 0 ], points[ size - 1 ], lineWidth );
}

void Renderer::FillRect( double left, double top, double width, double height ) {
	FillRect( Rect2D( left, top, left + width, top + height ) );
}
void Renderer::FillRect( const Vector2D& lefttop, const Vector2D& rightbottom ) {
	FillRect( Rect2D( lefttop, rightbottom ) );
}
void Renderer::FillRect( const Rect2D& rect ) {

}

void Renderer::FillCircle( const Vector2D& center, double r ) {
	FillCircle( center.x, center.y, r );
}
void Renderer::FillCircle( double xcenter, double ycenter, double r ) {

}

void Renderer::FillPolygon( const std::vector<Vector2D>& vecPoints ) {
	Vector2D* points = new Vector2D[ ( int )vecPoints.size() ];
	for( int i = 0; i < ( int )vecPoints.size(); ++i )
		points[ i ] = vecPoints[ i ];

	FillPolygon( points, vecPoints.size() );
}
void Renderer::FillPolygon( Vector2D* points, int size ) {

}

void Renderer::DrawModel( const Shader & shader, const Geometry & geo ) {
	glUseProgram( shader.handle );
	glBindVertexArray( geo.vao );

	glDrawElements( GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0 );
}