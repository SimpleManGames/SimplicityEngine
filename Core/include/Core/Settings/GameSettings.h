#ifndef _GAMESETTINGS_H
#define _GAMESETTINGS_H

#include "Settings.h"

#ifndef _STRING_H
#include "Defines/string.h"
#endif

class GameSettings : public Settings {
public:
	GameSettings();
	virtual ~GameSettings();

	virtual void Initialize( const std::tstring& filePath );

	void SetDefaultSceneName( const std::tstring& name );
	const std::tstring& GetDefaultSceneName() const;

protected:
	virtual void ParseSettingsFile( const std::tstring& valueName, const std::tstring& valueData );

private:

	std::tstring defaultSceneName;
};

#endif // _GAMESETTINGS_H
