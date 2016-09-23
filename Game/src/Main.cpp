#include "Main.h"

#include "Core/Engine.h"
#include "Core/Game/Game.h"

#include "Helpers/Singleton.h"
#include "Diagnostics/Logger.h"

#if defined (DEBUG) | defined(_DEBUG)
int _tmain( int argc, char* argv[ ] ) {
	UNREFERENCED_PARAMETER( argc );
	UNREFERENCED_PARAMETER( argv );

	WinMain( ( HINSTANCE )GetModuleHandle( NULL ), 0, 0, SW_SHOW );
}
#endif

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	UNREFERENCED_PARAMETER( hInstance );
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );
	UNREFERENCED_PARAMETER( nCmdShow );

#if defined (DEBUG) | defined(_DEBUG)
	HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, 0 );

	////Enable run-time memory leak check for debug builds.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(0);
#endif

	Singleton<Logger>::CreateInstance();
	Singleton<Logger>::GetInstance().Initialize();

	Engine engine( new Game() );
	int result = engine.MainLoop();

	Singleton<Logger>::GetInstance().Shutdown();
	Singleton<Logger>::DestroyInstance();

	return result;
}