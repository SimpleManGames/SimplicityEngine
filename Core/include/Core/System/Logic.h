#ifndef _LOGIC_H
#define _LOGIC_H

#include "System.h"
#include "Interfaces/IDrawable.h"

class AbstractGame;

class Logic : public System, public IDrawable {
public:
	Logic();
	virtual ~Logic();

	virtual bool Initialize();
	void Update();
	void Draw();
	virtual bool Shutdown();

	void SetGame( AbstractGame* game );

private:

	AbstractGame* game;
};

#endif