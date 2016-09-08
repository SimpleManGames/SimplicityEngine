#ifndef _ENGINE_H
#define _ENGINE_H

class AbstractGame;

class Engine {
public:
	Engine( AbstractGame* game );
	~Engine();

	int MainLoop();

private:

	int Initialize();
	void Draw();
	void Update();
	int ShutDown();

	bool CreateManagers();
	bool DestroyManagers();

	AbstractGame* game;
};

#endif // _ENGINE_H