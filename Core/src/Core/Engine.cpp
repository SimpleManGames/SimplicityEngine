#include "Core/Engine.h"

#ifndef _WINDOWS_
#include <Windows.h>
#endif

//System
#include "Core/System/System.h"

#include "Core\System\Logic.h"
#include "Core\System\MainWindow.h"
#include "Core\System\Graphics.h"
#include "Core\System\MainTimer.h"
#include "Core\System\Input.h"

#include "Core/System/Manager/SystemManager.h"
#include "Defines/Types/SystemType.h"

//Interface
#include "Interfaces/IDrawable.h"

//Helpers
#include "Helpers/Singleton.h"

//Diagnostics
#include "Diagnostics/Logger.h"

//Settings
#include "Core/Settings/WorldSettings.h"

//SceneGraph
#include "SceneGraph/Scene/Manager/SceneManager.h"

//Game
#include "Core/Game/AbstractGame.h"

namespace {
	const int INITIALIZATION_FAILED = 0x0001;
	const int SHUTDOWN_FAILED = 0x0010;
}

Engine::Engine( AbstractGame* game )
	:game( game ) {}

Engine::~Engine() {}

int Engine::MainLoop() {
	if( !Initialize() ) {
		Singleton<Logger>::GetInstance().Log( _T( "Initialization of the engine failed." ), LOGTYPE_ERROR );
		return INITIALIZATION_FAILED;
	}
	Singleton<Logger>::GetInstance().Log( _T( "Initialization of the engine was successful" ), LOGTYPE_INFO );

	// Seed the random number generator
	srand( GetTickCount() );

	MSG msg = {};
	while( msg.message != WM_QUIT ) {
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		Update();
		Draw();
	}

	if( !ShutDown() ) {
		Singleton<Logger>::GetInstance().Log( _T( "Shutdown of the engine failed." ), LOGTYPE_ERROR );
		return SHUTDOWN_FAILED;
	}

	return msg.wParam;
}

int Engine::Initialize() {
	if( !CreateManagers() )
		return FALSE;

	MainWindow* window = dynamic_cast< MainWindow* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::WINDOW_SYSTEM ) );
	if( window == nullptr )
		return FALSE;
	MainTimer* timer = dynamic_cast< MainTimer* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::TIMER_SYSTEM ) );
	if( timer == nullptr )
		return FALSE;
	Graphics* graphics = dynamic_cast< Graphics* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::GRAPHICS_SYSTEM ) );
	if( graphics == nullptr )
		return FALSE;
	Input* input = dynamic_cast< Input* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::INPUT_SYSTEM ) );
	if( input == nullptr )
		return false;
	Logic* logic = dynamic_cast< Logic* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::LOGIC_SYSTEM ) );
	if( logic == nullptr )
		return FALSE;

	if( !window->Initialize() )
		return FALSE;
	if( !timer->Initialize() )
		return FALSE;
	if( !graphics->Initialize() )
		return FALSE;
	if( !input->Initialize() )
		return FALSE;

	logic->SetGame( this->game );
	if( !logic->Initialize() )
		return FALSE;

	return TRUE;
}
void Engine::Draw() {
	Graphics* graphics = dynamic_cast< Graphics* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::GRAPHICS_SYSTEM ) );
	//graphics->BeginDraw();

	for( System* system : Singleton<SystemManager>::GetInstance().getDrawableSystems() ) {
		IDrawable* drawable_system = dynamic_cast< IDrawable* >( system );
		if( drawable_system->GetCanDraw() )
			drawable_system->Draw();
	}

	//graphics->EndDraw();
}
void Engine::Update() {
	for( System* system : Singleton<SystemManager>::GetInstance().getSystems() )
		system->Update();
}
int Engine::ShutDown() {
	if( !DestroyManagers() )
		return FALSE;

	return TRUE;
}

bool Engine::CreateManagers() {
	Singleton<WorldSettings>::CreateInstance();
	Singleton<SystemManager>::CreateInstance();
	Singleton<SceneManager>::CreateInstance();

	if( !Singleton<WorldSettings>::GetInstance().Initialize() )
		return false;
	if( !Singleton<SystemManager>::GetInstance().Initialize() )
		return false;

	return true;
}
bool Engine::DestroyManagers() {
	if( !Singleton<SystemManager>::GetInstance().Shutdown() )
		return false;
	if( !Singleton<WorldSettings>::GetInstance().Shutdown() )
		return false;

	Singleton<SceneManager>::DestroyInstance();
	Singleton<SystemManager>::DestroyInstance();
	Singleton<WorldSettings>::DestroyInstance();

	return true;
}