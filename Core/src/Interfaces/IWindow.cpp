#include "Interfaces/IWindow.h"

#include "Diagnostics/Logger.h"

#include "Helpers/Singleton.h"

#include "Core\Settings\WorldSettings.h"
#include "Core\Settings\ApplicationSettings.h"

#define GLEW_STATIC
#include "GLEW\glew.h"
#include "GLFW\glfw3.h"

IWindow::IWindow()
	: hDC( 0 )
	, hWindow( 0 )
	, hInstance( GetModuleHandle( NULL ) )

	, windowRect()

	, extendedStyle( 0 )
	, style( 0 )

	, pixelFormat( 0 )

	, windowClassname( _T( "" ) )
	, windowTitle( _T( "" ) )

	, windowWidth( Singleton<WorldSettings>::GetInstance().GetApplicationSettings().GetWindowWidth() )
	, windowHeight( Singleton<WorldSettings>::GetInstance().GetApplicationSettings().GetWindowHeight() ) {}
IWindow::~IWindow() {}

LRESULT CALLBACK IWindow::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	if( uMsg == WM_CREATE ) {
		// if the message is WM_CREATE, the lParam contains a pointer to a CREATESTRUCT
		// the CREATESTRUCT contains the "this" pointer from the CreateWindow method
		// the "this" pointer of our app is stored in the createstruct pcs->lpCreateParams
		CREATESTRUCT *pCS = ( CREATESTRUCT* )lParam;
		SetWindowLongPtr( hWnd, GWLP_USERDATA, ( LONG_PTR )pCS->lpCreateParams );
	} else {
		//retrieve the stored "this" pointer
		IWindow* window = ( IWindow* )( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );
		if( window != nullptr )
			return window->HandleEvent( hWnd, uMsg, wParam, lParam );
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

bool IWindow::MakeWindow() {
	this->windowRect = CreateWindowRect();

	this->windowClassname = GetWindowClassName();
	this->windowTitle = GetWindowTitle();

	if( !RegisterClass( &CreateWindowClass() ) ) {
		int value = GetLastError();
		Singleton<Logger>::GetInstance().Log( _T( "Register \"WNDCLASS\" failed." ), LOGTYPE_ERROR );
		return FALSE;
	}
	glfwInit();

	if( !SetupWindow() )
		return FALSE;
	if( !ErrorHandling() )
		return FALSE;


	if( !( hglrc = wglCreateContext( hDC ) ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "Failed to create the OpenGL RC" ), LOGTYPE_ERROR );
		return FALSE;
	}

	if( !( wglMakeCurrent( hDC, hglrc ) ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "Failed to make OpenGL RC current" ), LOGTYPE_ERROR );
		return FALSE;
	}
	if( !( winHandle = glfwCreateWindow( GetWindowWidth(), GetWindowHeight(), "Test", nullptr, nullptr ) ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "Failed to make GLFW Window" ), LOGTYPE_ERROR );
		return FALSE;
	}

	glewExperimental = true;
	glewInit();
	glClearColor( 1.0f, 0.5f, 0.5f, 1.0f );

	ShowWindow( this->hWindow, SW_SHOW );
	SetForegroundWindow( this->hWindow );
	SetFocus( this->hWindow );

	return TRUE;
}
bool IWindow::MakeGLWindow() {
	glfwInit();
	char * title = new char[ 255 ];
	sprintf( title, "%ls", this->GetWindowTitle().c_str() );
	winHandle = glfwCreateWindow( GetWindowWidth(), GetWindowHeight(), title, nullptr, nullptr );
	glfwMakeContextCurrent( winHandle );
	glewExperimental = true;
	glewInit();
	glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
	return TRUE;
}
bool IWindow::TerminateWindow() {
	LPCTSTR windowClassname = GetWindowClassName().c_str();

	if( this->hDC && !ReleaseDC( this->hWindow, this->hDC ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "Release \"DC\" failed." ), LOGTYPE_ERROR );
		this->hDC = NULL;
	}
	if( this->hWindow && !DestroyWindow( this->hWindow ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "Release \"HWND\" failed" ), LOGTYPE_ERROR );
		this->hWindow = NULL;
	}

	if( !UnregisterClass( this->windowClassname.c_str(), this->hInstance ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "Unregister \"WNDCLASS\" failed" ), LOGTYPE_ERROR );
		this->hInstance = NULL;
	}

	return TRUE;
}

const POINT IWindow::GetCenterPosition() const {
	int windowwidth = this->windowRect.right - this->windowRect.left;
	int windowheight = this->windowRect.bottom - this->windowRect.top;

	return POINT
	{
		GetSystemMetrics( SM_CXSCREEN ) / 2 - windowwidth / 2,
		GetSystemMetrics( SM_CYSCREEN ) / 2 - windowheight / 2
	};
}

void IWindow::SetExtendedStyle( DWORD extendedStyle ) { this->extendedStyle = extendedStyle; }
void IWindow::SetStyle( DWORD style ) { this->style = style; }

DWORD IWindow::GetExtentedStyle() const { return this->extendedStyle; }
DWORD IWindow::GetStyle() const { return this->style; }

RECT IWindow::GetWindowRect() const { return this->windowRect; }

bool IWindow::SetupWindow() {
	this->hWindow = CreateWindowEx( this->extendedStyle,
									this->windowClassname.c_str(),
									this->windowTitle.c_str(),
									this->style |
									WS_CLIPSIBLINGS |
									WS_CLIPCHILDREN,
									GetWindowPosition().x, GetWindowPosition().y,
									this->windowRect.right - this->windowRect.left,
									this->windowRect.bottom - this->windowRect.top,
									NULL,
									NULL,
									this->hInstance,
									this );

	int error = GetLastError();
	if( !this->hWindow ) {
		Singleton<Logger>::GetInstance().Log( _T( "Creation of our window failed." ), LOGTYPE_ERROR );
		return FALSE;
	}

	return TRUE;
}
bool IWindow::ErrorHandling() {
	//Check if we have a device context
	if( !( this->hDC = GetDC( this->hWindow ) ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "Can't create a \"GLDC\"." ), LOGTYPE_ERROR );
		return FALSE;
	}

	//Check the pixel format
	PIXELFORMATDESCRIPTOR pfd = CreateWindowPixelFormatDescription();

	this->pixelFormat = ChoosePixelFormat( this->hDC, &pfd );
	if( !this->pixelFormat ) {
		Singleton<Logger>::GetInstance().Log( _T( "Can't find a suitable \"PixelFormat\"." ), LOGTYPE_ERROR );
		return FALSE;
	}
	if( !SetPixelFormat( this->hDC, this->pixelFormat, &pfd ) ) {
		Singleton<Logger>::GetInstance().Log( _T( "Can't set the \"PixelFormat\"." ), LOGTYPE_ERROR );
		return FALSE;
	}

	return TRUE;
}

WNDCLASS IWindow::CreateWindowClass() {
	LPCTSTR windowClassname = GetWindowClassName().c_str();

	WNDCLASS wc;
	memset( &wc, NULL, sizeof( WNDCLASS ) );

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = ( WNDPROC )WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;

	//TODO: load the cursor and application icon!
	wc.hIcon = LoadIcon( NULL, IDI_WINLOGO );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );

	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;

	wc.lpszClassName = this->windowClassname.c_str();

	return wc;
}
RECT IWindow::CreateWindowRect() {
	return RECT
	{
		( long )0,
		( long )0,
		( long )GetWindowWidth(),
		( long )GetWindowHeight()
	};
}
PIXELFORMATDESCRIPTOR IWindow::CreateWindowPixelFormatDescription() {
	return PIXELFORMATDESCRIPTOR
	{
		sizeof( PIXELFORMATDESCRIPTOR ),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		GetWindowBitsPerPixel(),
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
}

long IWindow::GetWindowWidth() const { return windowWidth; }
long IWindow::GetWindowHeight() const {	return windowHeight; }

void IWindow::SetWindowWidth( long width ) { this->windowWidth = width; }
void IWindow::SetWindowHeight( long height ) { this->windowHeight = height; }

HDC IWindow::getWindowDeviceContext() const { return this->hDC; }
HWND IWindow::getWindowHandle() const { return this->hWindow; }
HINSTANCE IWindow::getWindowInstance() const { return this->hInstance; }