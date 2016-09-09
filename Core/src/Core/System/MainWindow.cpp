#include "Core/System/MainWindow.h"
#include "Core/System/Graphics.h"
#include "Core/System/Manager/SystemManager.h"

#include "Core/Settings/WorldSettings.h"
#include "Core/Settings/ApplicationSettings.h"

#include "Defines/Types/SystemType.h"
#include "Defines/string.h"

#include "Diagnostics/Logger.h"

#include "Helpers/Singleton.h"

#include "GLEW\glew.h"
#include "GLFW\glfw3.h"

MainWindow::MainWindow()
	:System( SystemType::WINDOW_SYSTEM ) {}
MainWindow::~MainWindow() {}

bool MainWindow::Initialize() {
	if( !MakeGLWindow() ) {
		Shutdown();
		return FALSE;
	}

	return TRUE;
}
void MainWindow::Update() {
	glfwMakeContextCurrent( winHandle );
	glfwPollEvents();
	glfwSwapBuffers( winHandle );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
bool MainWindow::Shutdown() {
	ApplicationSettings settings = Singleton<WorldSettings>::GetInstance().GetApplicationSettings();

	if( settings.GetFullscreen() ) {
		ChangeDisplaySettings( NULL, 0 );
		ShowCursor( TRUE );
	}

	TerminateWindow();

	return TRUE;
}

LRESULT MainWindow::HandleEvent( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	switch( uMsg ) {
		case WM_ACTIVATE:
		{
			if( !HIWORD( wParam ) )
				Activate();
			else
				Deactivate();

			return 0;
		}

		case WM_SYSCOMMAND:
		{
			switch( wParam ) {
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
			}
			break;
		}

		case WM_SIZE:
		{
			Graphics* graphics = dynamic_cast< Graphics* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::GRAPHICS_SYSTEM ) );
			return 0;
		}

		case WM_CLOSE:
		{
			PostQuitMessage( 0 );
			return 0;
		}
	}

	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

BYTE MainWindow::GetWindowBitsPerPixel() const {
	return Singleton<WorldSettings>::GetInstance().GetApplicationSettings().GetBitsPerPixel();
}

const std::tstring MainWindow::GetWindowTitle() const {
	return Singleton<WorldSettings>::GetInstance().GetApplicationSettings().GetWindowTitle();
}
const std::tstring MainWindow::GetWindowClassName() const {
	return Singleton<WorldSettings>::GetInstance().GetApplicationSettings().GetWindowTitle();
}

const POINT MainWindow::GetWindowPosition() const {
	return GetCenterPosition();
}