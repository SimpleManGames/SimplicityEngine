#include "Core/Game/Game.h"

#include "Helpers/Singleton.h"

#include "SceneGraph/Scene/MyScene.h"
#include "SceneGraph/Scene/Manager/SceneManager.h"

Game::Game() {}
Game::~Game() {}

bool Game::Initialize() {
	//Add all the scenes you need
	Singleton<SceneManager>::GetInstance().AddScene( new MyScene() );

	//Active your main scene
	Singleton<SceneManager>::GetInstance().SetActiveScene( _T( "MyScene" ) );

	return true;
}
bool Game::Shutdown() {
	return true;
}
