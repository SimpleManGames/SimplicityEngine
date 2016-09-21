#include "Core/Engine.h"

#ifndef _WINDOWS_
#include <Windows.h>
#endif

//System
#include "Core/System/System.h"
#include "Defines\systemdefines.h"

#include "Core/System/Manager/SystemManager.h"
#include "Defines/Types/SystemType.h"

#include "Core\System\MainWindow.h"
#include "Core\System\Graphics.h"
#include "Core\System\Input.h"
#include "Core\System\Logic.h"
#include "Core\System\MainTimer.h"

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
	if( !CreateManagers() ) {
		Singleton<Logger>::GetInstance().Log( _T( "Failed to create managers" ), LOGTYPE_ERROR );
		return FALSE;
	}
	Singleton<Logger>::GetInstance().Log( _T( "Managers successfully created" ), LOGTYPE_INFO );

	MainWindow* window = GetSystem(MainWindow, SystemType::WINDOW_SYSTEM);
	if( window == nullptr ) {
		Singleton<Logger>::GetInstance().Log( _T( "System Manager failed to get the Window System" ), LOGTYPE_ERROR );
		return FALSE;
	}
	MainTimer* timer = GetSystem(MainTimer, SystemType::TIMER_SYSTEM);
	if( timer == nullptr ) {
		Singleton<Logger>::GetInstance().Log( _T( "System Manager failed to get the Timer System" ), LOGTYPE_ERROR );
		return FALSE;
	}
	Graphics* graphics = GetSystem(Graphics, SystemType::GRAPHICS_SYSTEM);
	if( graphics == nullptr ) {
		Singleton<Logger>::GetInstance().Log( _T( "System Manager failed to get the Graphics System" ), LOGTYPE_ERROR );
		return FALSE;
	}
	Input* input = GetSystem(Input, SystemType::INPUT_SYSTEM);
	if( input == nullptr ) {
		Singleton<Logger>::GetInstance().Log( _T( "System Manager failed to get the Input System" ), LOGTYPE_ERROR );
		return FALSE;
	}
	Logic* logic = GetSystem(Logic, SystemType::LOGIC_SYSTEM);
	if( logic == nullptr ) {
		Singleton<Logger>::GetInstance().Log( _T( "System Manager failed to get the Logic System" ), LOGTYPE_ERROR );
		return FALSE;
	}
	Singleton<Logger>::GetInstance().Log( _T( "All system pointers were successful" ), LOGTYPE_INFO );

	if( !window->Initialize() ) {
		Singleton<Logger>::GetInstance().Log( _T( "Window initialization failed" ), LOGTYPE_ERROR );
		return FALSE;
	}
	if( !timer->Initialize() ) {
		Singleton<Logger>::GetInstance().Log( _T( "Timer initialization failed" ), LOGTYPE_ERROR );
		return FALSE;
	}
	if( !graphics->Initialize() ) {
		Singleton<Logger>::GetInstance().Log( _T( "Graphic initialization failed" ), LOGTYPE_ERROR );
		return FALSE;
	}
	if( !input->Initialize() ) {
		Singleton<Logger>::GetInstance().Log( _T( "Input initialization failed" ), LOGTYPE_ERROR );
		return FALSE;
	}

	logic->SetGame( this->game );
	if( !logic->Initialize() ) {
		Singleton<Logger>::GetInstance().Log( _T( "Logic initialization failed" ), LOGTYPE_ERROR );
		return FALSE;
	}
	Singleton<Logger>::GetInstance().Log( _T( "All system initializaton was successful" ), LOGTYPE_INFO );

	return TRUE;
}
void Engine::Draw() {
	Graphics* graphics = dynamic_cast< Graphics* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::GRAPHICS_SYSTEM ) );

	for( System* system : Singleton<SystemManager>::GetInstance().getDrawableSystems() ) {
		IDrawable* drawable_system = dynamic_cast< IDrawable* >( system );
		if( drawable_system->GetCanDraw() )
			drawable_system->Draw();
	}
}
void Engine::Update() {
	for( System* system : Singleton<SystemManager>::GetInstance().getSystems() )
		system->Update();

	Singleton<SceneManager>::GetInstance().Update();
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