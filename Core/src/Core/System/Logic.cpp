#include "Core/System/Logic.h"
#include "Core/Game/AbstractGame.h"

#include "SceneGraph/Scene/Manager/SceneManager.h"

#include "Helpers/Singleton.h"

#include "Defines\Types\SystemType.h"
#include "Defines\assert.h"
#include "Defines/deletemacros.h"

Logic::Logic()
	:System( SystemType::LOGIC_SYSTEM )
	, game( nullptr ) {}
Logic::~Logic() {}

bool Logic::Initialize() {
	//Game cannot be null!
	assert( this->game != nullptr );

	if( !game->Initialize() )
		return false;

	if( !Singleton<SceneManager>::GetInstance().Initialize() )
		return false;

	return true;
}
void Logic::Update() {
	Singleton<SceneManager>::GetInstance().Update();
}
void Logic::Draw() {
	if( Singleton<SceneManager>::GetInstance().GetCanDraw() )
		Singleton<SceneManager>::GetInstance().Draw();
}
bool Logic::Shutdown() {
	if( !Singleton<SceneManager>::GetInstance().Shutdown() )
		return false;

	if( !game->Shutdown() )
		return false;

	return true;
}

void Logic::SetGame( AbstractGame* game ) {
	this->game = game;
}