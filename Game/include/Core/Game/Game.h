#ifndef _GAME_H
#define _GAME_H

#include "Core/Game/AbstractGame.h"

class Game : public AbstractGame
{
public:
	Game();
	virtual ~Game();

	virtual bool Initialize();
	virtual bool Shutdown();
};

#endif