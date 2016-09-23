#include "Camera.h"

#include <iostream>

void Camera::Update( const Input * i, const MainTimer * t ) {

	azimuth -= i->getMouseHorz() * t->deltaTime * sensitivity;
	altitude += i->getMouseVert() * t->deltaTime * sensitivity;

	altitude = glm::clamp( altitude, -glm::pi<float>() / 2 + 0.0001f, glm::pi<float>() / 2 - 0.0001f );

	glm::mat4 tbn = glm::eulerAngleYXZ( azimuth, altitude, 0.0f );

	glm::vec3 right = glm::vec3( tbn[ 0 ] );
	glm::vec3 up = glm::vec3( tbn[ 1 ] );
	direction = glm::vec3( tbn[ 2 ] );

	glm::vec3 moveDir = glm::vec3( 0, 0, 0 );

	if( i->GetKeyState( 'W' ) == KeyState::DOWN ) moveDir += direction;
	if( i->GetKeyState( 'S' ) == KeyState::DOWN ) moveDir -= direction;

	if( i->GetKeyState( 'A' ) == KeyState::DOWN ) moveDir += right;
	if( i->GetKeyState( 'D' ) == KeyState::DOWN ) moveDir -= right;

	if( i->GetKeyState( ' ' ) == KeyState::DOWN ) moveDir += up;
	if( i->GetKeyState( 340 ) == KeyState::DOWN ) moveDir -= up;

	if( glm::length( moveDir ) >= .7f ) {
		moveDir = glm::normalize( moveDir );
		position += moveDir * t->deltaTime * speed;
	}
}