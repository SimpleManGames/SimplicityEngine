#include "Core/Settings/ApplicationSettings.h"

#ifndef _PROGRAMDEFAULTS_H
#include "Defines/programdefaults.h"
#endif

ApplicationSettings::ApplicationSettings()
	:Settings()
	, windowWidth( 1280 )
	, windowHeight( 720 )
	, windowBitsPerPixel( constants::BITS_PER_PIXEL_16 )
	, fullscreen( false )
	, windowTitle( _T( "" ) )
	, contentRootPath( _T( "./Resources/" ) ) {}
ApplicationSettings::~ApplicationSettings() {}

void ApplicationSettings::SetWindowWidth( int width ) {	this->windowWidth = width; }
int ApplicationSettings::GetWindowWidth() const { return this->windowWidth; }
void ApplicationSettings::SetWindowHeight( int height ) { this->windowHeight = height; }
int ApplicationSettings::GetWindowHeight() const { return this->windowHeight; }
void ApplicationSettings::SetBitsPerPixel( unsigned char bits ) { this->windowBitsPerPixel = bits; }
unsigned char ApplicationSettings::GetBitsPerPixel() const { return this->windowBitsPerPixel; }

void ApplicationSettings::SetFullscreen( int fullscreen ) { this->fullscreen = fullscreen == constants::TRUE; }
bool ApplicationSettings::GetFullscreen() const { return this->fullscreen; }

void ApplicationSettings::SetWindowTitle( const std::tstring& title ) { this->windowTitle = title; }
const std::tstring& ApplicationSettings::GetWindowTitle() const { return this->windowTitle; }
void ApplicationSettings::SetContentRootPath( const std::tstring& path ) { this->contentRootPath = path; }
const std::tstring& ApplicationSettings::GetContentRootPath() const { return this->contentRootPath; }

void ApplicationSettings::ParseSettingsFile( const std::tstring& valueName, const std::tstring& valueData ) {
	if( valueName == _T( "WINDOWWIDTH" ) )
		SetWindowWidth( _tstoi( valueData.c_str() ) );
	else if( valueName == _T( "WINDOWHEIGHT" ) )
		SetWindowHeight( _tstoi( valueData.c_str() ) );
	else if( valueName == _T( "BITSPERPIXEL" ) )
		SetBitsPerPixel( _tstoi( valueData.c_str() ) );
	else if( valueName == _T( "FULLSCREEN" ) )
		SetFullscreen( _tstoi( valueData.c_str() ) );
	else if( valueName == _T( "WINDOWTITLE" ) )
		SetWindowTitle( valueData );
	else if( valueName == _T( "ROOTPATH" ) )
		SetContentRootPath( valueData );
}