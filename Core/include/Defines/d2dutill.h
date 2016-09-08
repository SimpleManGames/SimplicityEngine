#ifndef _2DUTILL_H
#define _2DUTILL_H

// Let VC++ know we are compiling for WinXP and up.  This let's us use
// API functions specific to WinXP (e.g., WM_INPUT API).
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600 // Vista
#endif

// Enable extra D3D debugging in debug builds if using the debug DirectX runtime.  
// This makes D3D objects work well in the debugger watch window, but slows down 
// performance slightly.
#if defined(DEBUG) || defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

//C Runtime Header Files
//----------------------
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <dwrite.h>
#include <wincodec.h>
#include <d2d1.h>
#include <d2d1helper.h>

// libs used for Direct2D
//-----------------------
#pragma comment(lib, "d2d1.lib")			
#pragma comment(lib, "WindowsCodecs.lib")	//WIC
#pragma comment(lib, "dwrite.lib")			//WIC

//inline bool D2D_COLOR_F_isEqual(const D2D_COLOR_F& c1, const D2D_COLOR_F& c2)
//{
//	return fabs(c1.r - c2.r) < FLT_EPSILON &&  fabs(c1.g - c2.g) < FLT_EPSILON &&  fabs(c1.b - c2.b) < FLT_EPSILON &&  fabs(c1.a - c2.a) < FLT_EPSILON;
//}
//inline bool D2D_COLOR_F_notEqual(const D2D_COLOR_F& c1, const D2D_COLOR_F& c2)
//{
//	return !D2D_COLOR_F_isEqual(c1, c2);
//}

#endif //_D3DUTILL_H