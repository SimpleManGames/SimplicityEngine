#ifndef _WINDOW_H
#define _WINDOW_H

#include "System.h"
#include "Interfaces/IWindow.h"

class MainWindow : public System, public IWindow {
public:
	MainWindow();
	virtual ~MainWindow();

	virtual bool Initialize();
	virtual void Update();
	virtual bool Shutdown();

	virtual LRESULT HandleEvent( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );

	virtual BYTE GetWindowBitsPerPixel() const;

	virtual const std::tstring GetWindowTitle() const;
	virtual const std::tstring GetWindowClassName() const;

	virtual const POINT GetWindowPosition() const;

private:
};

#endif //_WINDOW_H