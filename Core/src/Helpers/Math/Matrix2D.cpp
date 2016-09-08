#include "Helpers/Math/Matrix2D.h"

#ifndef _UNORDERED_SET_
#include <unordered_set>
#endif

Matrix2D::Matrix2D() {
	// initially identity matrix
	Identity();
}
Matrix2D::Matrix2D( float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8 ) {
	m[ 0 ] = m0; m[ 1 ] = m1; m[ 2 ] = m2;
	m[ 3 ] = m3; m[ 4 ] = m4; m[ 5 ] = m5;
	m[ 6 ] = m6; m[ 7 ] = m7; m[ 8 ] = m8;
}

float Matrix2D::GetDeterminant() {
	return m[ 0 ] * ( m[ 4 ] * m[ 8 ] - m[ 5 ] * m[ 7 ] ) - m[ 1 ] * ( m[ 3 ] * m[ 8 ] - m[ 5 ] * m[ 6 ] ) + m[ 2 ] * ( m[ 3 ] * m[ 7 ] - m[ 4 ] * m[ 6 ] );
}

inline Matrix2D& Matrix2D::Identity() {
	m[ 0 ] = m[ 4 ] = m[ 8 ] = 1.0f;
	m[ 1 ] = m[ 2 ] = m[ 3 ] = m[ 5 ] = m[ 6 ] = m[ 7 ] = 0.0f;
	return *this;
}
Matrix2D Matrix2D::Transpose() {
	Matrix2D matTranspose = *this;

	std::swap( matTranspose[ 1 ], matTranspose[ 3 ] );
	std::swap( matTranspose[ 2 ], matTranspose[ 6 ] );
	std::swap( matTranspose[ 5 ], matTranspose[ 7 ] );

	return matTranspose;
}
Matrix2D Matrix2D::Invert() {
	//tmp[0] = m[4] * m[8] - m[5] * m[7];
	//tmp[1] = m[1] * m[8] - m[2] * m[7];
	//tmp[2] = m[1] * m[5] - m[2] * m[4];
	//tmp[3] = m[3] * m[8] - m[5] * m[6];
	//tmp[4] = m[0] * m[8] - m[2] * m[6];
	//tmp[5] = m[0] * m[5] - m[2] * m[3];
	//tmp[6] = m[3] * m[7] - m[4] * m[6];
	//tmp[7] = m[0] * m[7] - m[1] * m[6];
	//tmp[8] = m[0] * m[4] - m[1] * m[3];

	//tmp[1] *= -1;
	//tmp[3] *= -1;
	//tmp[5] *= -1;
	//tmp[7] *= -1;

	float determinant, invDeterminant;
	float tmp[ 9 ];

	tmp[ 0 ] = m[ 4 ] * m[ 8 ] - m[ 5 ] * m[ 7 ];
	tmp[ 1 ] = m[ 2 ] * m[ 7 ] - m[ 1 ] * m[ 8 ];
	tmp[ 2 ] = m[ 1 ] * m[ 5 ] - m[ 2 ] * m[ 4 ];
	tmp[ 3 ] = m[ 5 ] * m[ 6 ] - m[ 3 ] * m[ 8 ];
	tmp[ 4 ] = m[ 0 ] * m[ 8 ] - m[ 2 ] * m[ 6 ];
	tmp[ 5 ] = m[ 2 ] * m[ 3 ] - m[ 0 ] * m[ 5 ];
	tmp[ 6 ] = m[ 3 ] * m[ 7 ] - m[ 4 ] * m[ 6 ];
	tmp[ 7 ] = m[ 1 ] * m[ 6 ] - m[ 0 ] * m[ 7 ];
	tmp[ 8 ] = m[ 0 ] * m[ 4 ] - m[ 1 ] * m[ 3 ];

	// check determinant if it is 0
	determinant = m[ 0 ] * tmp[ 0 ] + m[ 1 ] * tmp[ 3 ] + m[ 2 ] * tmp[ 6 ];
	if( fabs( determinant ) <= EPSILON )
		return Identity(); // cannot inverse, make it idenety matrix

	// divide by the determinant
	invDeterminant = 1.0f / determinant;

	Matrix2D matInverse = Matrix2D( invDeterminant * tmp[ 0 ],
									invDeterminant * tmp[ 1 ],
									invDeterminant * tmp[ 2 ],
									invDeterminant * tmp[ 3 ],
									invDeterminant * tmp[ 4 ],
									invDeterminant * tmp[ 5 ],
									invDeterminant * tmp[ 6 ],
									invDeterminant * tmp[ 7 ],
									invDeterminant * tmp[ 8 ] );

	//m[0] = invDeterminant * tmp[0];
	//m[1] = invDeterminant * tmp[1];
	//m[2] = invDeterminant * tmp[2];
	//m[3] = invDeterminant * tmp[3];
	//m[4] = invDeterminant * tmp[4];
	//m[5] = invDeterminant * tmp[5];
	//m[6] = invDeterminant * tmp[6];
	//m[7] = invDeterminant * tmp[7];
	//m[8] = invDeterminant * tmp[8];

	return matInverse;
}

Vector2D Matrix2D::GetTranslation() const {
	return Vector2D( m[ 2 ], m[ 5 ] );
}
Vector2D Matrix2D::GetScale() const {
	return Vector2D( m[ 0 ], m[ 4 ] );
}
double Matrix2D::GetRotation() {
	if( ( m[ 1 ] != ( -1 * m[ 3 ] ) ) || ( m[ 4 ] != m[ 0 ] ) )
		return -1.0;
	else {
		double scale_factor = sqrt( ( m[ 0 ] * m[ 4 ] - m[ 3 ] * m[ 1 ] ) );
		return acos( m[ 0 ] / scale_factor ); // For radians
	}
}

Matrix2D Matrix2D::operator+( const Matrix2D& rhs ) const {
	return Matrix2D( m[ 0 ] + rhs[ 0 ], m[ 1 ] + rhs[ 1 ], m[ 2 ] + rhs[ 2 ],
					 m[ 3 ] + rhs[ 3 ], m[ 4 ] + rhs[ 4 ], m[ 5 ] + rhs[ 5 ],
					 m[ 6 ] + rhs[ 6 ], m[ 7 ] + rhs[ 7 ], m[ 8 ] + rhs[ 8 ] );
}
Matrix2D Matrix2D::operator-( const Matrix2D& rhs ) const {
	return Matrix2D( m[ 0 ] - rhs[ 0 ], m[ 1 ] - rhs[ 1 ], m[ 2 ] - rhs[ 2 ],
					 m[ 3 ] - rhs[ 3 ], m[ 4 ] - rhs[ 4 ], m[ 5 ] - rhs[ 5 ],
					 m[ 6 ] - rhs[ 6 ], m[ 7 ] - rhs[ 7 ], m[ 8 ] - rhs[ 8 ] );
}
Matrix2D& Matrix2D::operator+=( const Matrix2D& rhs ) {
	m[ 0 ] += rhs[ 0 ];  m[ 1 ] += rhs[ 1 ];  m[ 2 ] += rhs[ 2 ];
	m[ 3 ] += rhs[ 3 ];  m[ 4 ] += rhs[ 4 ];  m[ 5 ] += rhs[ 5 ];
	m[ 6 ] += rhs[ 6 ];  m[ 7 ] += rhs[ 7 ];  m[ 8 ] += rhs[ 8 ];
	return *this;
}
Matrix2D& Matrix2D::operator-=( const Matrix2D& rhs ) {
	m[ 0 ] -= rhs[ 0 ];  m[ 1 ] -= rhs[ 1 ];  m[ 2 ] -= rhs[ 2 ];
	m[ 3 ] -= rhs[ 3 ];  m[ 4 ] -= rhs[ 4 ];  m[ 5 ] -= rhs[ 5 ];
	m[ 6 ] -= rhs[ 6 ];  m[ 7 ] -= rhs[ 7 ];  m[ 8 ] -= rhs[ 8 ];
	return *this;
}

Matrix2D Matrix2D::operator*( const Matrix2D& rhs ) const {
	return Matrix2D( m[ 0 ] * rhs[ 0 ] + m[ 3 ] * rhs[ 1 ] + m[ 6 ] * rhs[ 2 ],
					 m[ 1 ] * rhs[ 0 ] + m[ 4 ] * rhs[ 1 ] + m[ 7 ] * rhs[ 2 ],
					 m[ 2 ] * rhs[ 0 ] + m[ 5 ] * rhs[ 1 ] + m[ 8 ] * rhs[ 2 ],
					 m[ 0 ] * rhs[ 3 ] + m[ 3 ] * rhs[ 4 ] + m[ 6 ] * rhs[ 5 ],
					 m[ 1 ] * rhs[ 3 ] + m[ 4 ] * rhs[ 4 ] + m[ 7 ] * rhs[ 5 ],
					 m[ 2 ] * rhs[ 3 ] + m[ 5 ] * rhs[ 4 ] + m[ 8 ] * rhs[ 5 ],
					 m[ 0 ] * rhs[ 6 ] + m[ 3 ] * rhs[ 7 ] + m[ 6 ] * rhs[ 8 ],
					 m[ 1 ] * rhs[ 6 ] + m[ 4 ] * rhs[ 7 ] + m[ 7 ] * rhs[ 8 ],
					 m[ 2 ] * rhs[ 6 ] + m[ 5 ] * rhs[ 7 ] + m[ 8 ] * rhs[ 8 ] );
}
Matrix2D& Matrix2D::operator*=( const Matrix2D& rhs ) {
	*this = *this * rhs;
	return *this;
}

bool Matrix2D::operator==( const Matrix2D& rhs ) const {
	return ( m[ 0 ] == rhs[ 0 ] ) && ( m[ 1 ] == rhs[ 1 ] ) && ( m[ 2 ] == rhs[ 2 ] ) &&
		( m[ 3 ] == rhs[ 3 ] ) && ( m[ 4 ] == rhs[ 4 ] ) && ( m[ 5 ] == rhs[ 5 ] ) &&
		( m[ 6 ] == rhs[ 6 ] ) && ( m[ 7 ] == rhs[ 7 ] ) && ( m[ 8 ] == rhs[ 8 ] );
}
bool Matrix2D::operator!=( const Matrix2D& rhs ) const {
	return ( m[ 0 ] != rhs[ 0 ] ) || ( m[ 1 ] != rhs[ 1 ] ) || ( m[ 2 ] != rhs[ 2 ] ) ||
		( m[ 3 ] != rhs[ 3 ] ) || ( m[ 4 ] != rhs[ 4 ] ) || ( m[ 5 ] != rhs[ 5 ] ) ||
		( m[ 6 ] != rhs[ 6 ] ) || ( m[ 7 ] != rhs[ 7 ] ) || ( m[ 8 ] != rhs[ 8 ] );
}

float Matrix2D::operator[]( int index ) const {
	return m[ index ];
}
float& Matrix2D::operator[]( int index ) {
	return m[ index ];
}

Matrix2D& Matrix2D::operator=( const Matrix2D& other ) {
	for( int i = 0; i < MAXNUMBER; ++i )
		this->m[ i ] = other.m[ i ];

	return *this;
}

Matrix2D Matrix2D::CreateIdentityMatrix() {
	return Matrix2D();
}

Matrix2D Matrix2D::CreateRotationMatrix( double angle ) {
	return Matrix2D( ( float )cos( angle ), ( float )-sin( angle ), 0.0f,
		( float )sin( angle ), ( float )cos( angle ), 0.0f,
					 0.0f, 0.0f, 1.0f );
}

Matrix2D Matrix2D::CreateScalingMatrix( double scale ) {
	return CreateScalingMatrix( scale, scale );
}
Matrix2D Matrix2D::CreateScalingMatrix( const Vector2D& scaleXY ) {
	return CreateScalingMatrix( scaleXY.x, scaleXY.y );
}
Matrix2D Matrix2D::CreateScalingMatrix( double scaleX, double scaleY ) {
	return Matrix2D( ( float )scaleX, 0.0f, 0.0f,
					 0.0f, ( float )scaleY, 0.0f,
					 0.0f, 0.0f, 1.0f );
}

Matrix2D Matrix2D::CreateTranslationMatrix( const Vector2D& origin ) {
	return Matrix2D( 1.0f, 0.0f, ( float )origin.x,
					 0.0f, 1.0f, ( float )origin.y,
					 0.0f, 0.0f, 1.0f );
}
Matrix2D Matrix2D::CreateTranslationMatrix( double tx, double ty ) {
	return CreateTranslationMatrix( Vector2D( tx, ty ) );
}

const D2D1_MATRIX_3X2_F& Matrix2D::ToMatrix3x2F() {
	D2D1::Matrix3x2F mat;

	mat._11 = ( FLOAT )m[ 0 ];
	mat._12 = ( FLOAT )m[ 1 ];
	mat._21 = ( FLOAT )m[ 3 ];
	mat._22 = ( FLOAT )m[ 4 ];
	mat._31 = ( FLOAT )m[ 2 ];
	mat._32 = ( FLOAT )m[ 5 ];

	//mat._11 = (FLOAT)m[0];
	//mat._12 = (FLOAT)dirX.y;
	//mat._21 = (FLOAT)dirY.x;
	//mat._22 = (FLOAT)m[4];
	//mat._31 = (FLOAT)m[2];
	//mat._32 = (FLOAT)m[5];

	return mat;
}