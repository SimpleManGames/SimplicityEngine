#ifndef _APPLICATIONSETTINGS_H
#define _APPLICATIONSETTINGS_H

#include "Settings.h"

#ifndef _STRING_H
#include "Defines/string.h"
#endif

class ApplicationSettings : public Settings {
public:
	ApplicationSettings();
	virtual ~ApplicationSettings();

	void SetWindowWidth( int width );
	int GetWindowWidth() const;
	void SetWindowHeight( int height );
	int GetWindowHeight() const;
	void SetBitsPerPixel( unsigned char bits );
	unsigned char GetBitsPerPixel() const;
	void SetFullscreen( int fullscreen );
	bool GetFullscreen() const;

	void SetWindowTitle( const std::tstring& title );
	const std::tstring& GetWindowTitle() const;
	void SetContentRootPath( const std::tstring& path );
	const std::tstring& GetContentRootPath() const;

protected:
	virtual void ParseSettingsFile( const std::tstring& valueName, const std::tstring& valueData );

private:

	int windowWidth;
	int windowHeight;
	unsigned char windowBitsPerPixel;

	bool fullscreen;

	std::tstring windowTitle;
	std::tstring contentRootPath;
};

#endif // _APPLICATIONSETTING_H