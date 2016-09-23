#ifndef _IWINDOW_H
#define _IWINDOW_H

#ifndef _WINDOWS_
	#include <windows.h>
#endif
#ifndef _STRING_H
	#include "Defines/string.h"
#endif

class IWindow
{
	friend class MainWindow;

public:
	IWindow();
	virtual ~IWindow();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	virtual LRESULT HandleEvent(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) = 0;

	virtual long GetWindowWidth() const;
	virtual long GetWindowHeight() const;

	virtual BYTE GetWindowBitsPerPixel() const = 0;

	virtual const std::tstring GetWindowTitle() const = 0;
	virtual const std::tstring GetWindowClassName() const = 0;

	virtual const POINT GetWindowPosition() const = 0;

	HDC getWindowDeviceContext() const;
	HWND getWindowHandle() const;
	HINSTANCE getWindowInstance() const;

	struct GLFWwindow * GetWindowHandle() const { return winHandle; }

protected:
	bool MakeWindow();
	bool MakeGLWindow();
	bool TerminateWindow();

	const POINT GetCenterPosition() const;

	void SetExtendedStyle(DWORD extendedStyle);
	void SetStyle(DWORD style);

	DWORD GetExtentedStyle() const;
	DWORD GetStyle() const;

	RECT GetWindowRect() const;

	void SetWindowWidth(long width);
	void SetWindowHeight(long height);

private:
	bool SetupWindow();
	bool ErrorHandling();

	struct GLFWwindow * winHandle; 

	WNDCLASS CreateWindowClass();
	RECT CreateWindowRect();
	PIXELFORMATDESCRIPTOR CreateWindowPixelFormatDescription();

	HDC             hDC;
	HWND            hWindow;
	HINSTANCE       hInstance;
	HGLRC			hglrc;

	RECT			windowRect;

	DWORD			extendedStyle;
	DWORD			style;

	unsigned int	pixelFormat;

	std::tstring	windowClassname;
	std::tstring	windowTitle;

	long			windowWidth;
	long			windowHeight;
};

#endif //_IWINDOW_H