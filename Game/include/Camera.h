#ifndef _CAMERA_H
#define _CAMERA_H
#define GLM_SWIZZLE
#include <GLM\glm.hpp>
#include <GLM\ext.hpp>

#include "Core\System\Input.h"
#include "Core\System\MainTimer.h"
#include "Defines/Types/InputType.h"

class Camera {
private:
	glm::vec3 position;
	glm::vec3 direction;
	float aspect, fov, n, f;
	float azimuth, altitude;

	float speed = 10;
	float sensitivity = .1f;
public:
	Camera( float fov = 45.f, float a = 16.f / 9.f, float n = 1.f, float f = 100.f )
		: fov( fov ), aspect( a ), n( n ), f( f ), direction( 0, 0, 1 ), azimuth( 0 ), altitude( 0 ) {}

	void Update( const Input * i, const MainTimer * t );

	void LookAt( const glm::vec3 & target ) { direction = glm::normalize( target - position ); }
	void JumpTo( const glm::vec3 & loc ) { position = loc; }

	glm::mat4 GetView() const { return glm::lookAt( position, position + direction, glm::vec3( 0, 1, 0 ) ); }
	glm::mat4 GetProj() const { return glm::perspective( fov, aspect, n, f ); }
};


#endif // !_CAMERA_H
