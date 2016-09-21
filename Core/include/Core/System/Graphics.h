#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "Core/System/System.h"
#include "Interfaces/IDrawable.h"

#ifndef _2DUTILL_H
#include "Defines/d2dutill.h"
#endif

class MainWindow;

class Graphics : public System, public IDrawable {
public:
	Graphics();
	virtual ~Graphics();

	virtual bool Initialize();
	virtual void Update();
	virtual void Draw();
	virtual bool Shutdown();

private:
	MainWindow * mainWindow;
};

#endif // !_GRAPHICS_H