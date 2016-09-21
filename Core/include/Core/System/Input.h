#ifndef _INPUT_H
#define _INPUT_H

#include "Core/System/System.h"
#include "Core\System\MainWindow.h"

#include "Defines\Types\InputType.h"

class Input : public System {
public:
	Input();
	virtual ~Input();

	virtual bool Initialize();
	virtual void Update();
	virtual bool Shutdown();

	KeyState GetKeyState( int key ) const { return keys[ key ]; }

	float getMouseHorz() const { return mouseHor; }
	float getMouseVert() const { return mouseVer; }

private:
	struct GLFWwindow * winHandle;
	KeyState keys[ 350 ];
	double mouseXCur, mouseYCur, mouseXPrev, mouseYPrev;
	float mouseHor, mouseVer;
};

#endif // !_INPUT_H