#include "Core\System\Input.h"

#include "Helpers\Singleton.h"
#include "Core\System\Manager\SystemManager.h"

#include "GLFW\glfw3.h"

#include <cstring>

Input::Input()
	: System( SystemType::INPUT_SYSTEM ) {}

Input::~Input() {}

bool Input::Initialize() {
	memset( keys, 0, 350 * sizeof( KeyState ) );
	MainWindow* win = dynamic_cast< MainWindow* > ( Singleton<SystemManager>::GetInstance().getSystem( SystemType::WINDOW_SYSTEM ) );
	if( !( winHandle = win->GetWindowHandle() ) )
		return false;
	glfwSetInputMode( winHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	mouseXCur = mouseXPrev = mouseYCur = mouseYPrev = mouseHor = mouseVer = 0;

	return true;
}

void Input::Update() {
	for( int i = 0; i < 350; ++i ) {
		int state = glfwGetKey( winHandle, i );

		if( ( keys[ i ] == KeyState::UP || keys[ i ] == KeyState::RELEASE ) && state == GLFW_PRESS ) {
			keys[ i ] = KeyState::PRESS;
		} else if( ( keys[ i ] == KeyState::DOWN || keys[ i ] == KeyState::PRESS ) && state == GLFW_RELEASE ) {
			keys[ i ] = KeyState::RELEASE;
		} else if( keys[ i ] == KeyState::PRESS ) {
			keys[ i ] = KeyState::DOWN;
		} else if( keys[ i ] == KeyState::RELEASE ) {
			keys[ i ] = KeyState::UP;
		}
	}

	int w, h;

	glfwGetWindowSize( winHandle, &w, &h );

	mouseXPrev = mouseXCur;
	mouseYPrev = mouseYCur;

	glfwGetCursorPos( winHandle, &mouseXCur, &mouseYCur );
	//glfwSetCursorPos( winHandle, w / 2, h / 2 );

	mouseHor = mouseXCur - mouseXPrev;
	mouseVer = mouseYCur - mouseYPrev;
}

bool Input::Shutdown() {
	return true;
}
