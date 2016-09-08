#ifndef _WORLDSETTINGS_H
#define _WORLDSETTINGS_H

#include "Helpers/Manager.h"

#include "ApplicationSettings.h"
#include "PhyxSettings.h"
#include "GameSettings.h"

class WorldSettings : public Manager {
public:
	WorldSettings();
	virtual ~WorldSettings();

	virtual bool Initialize();
	virtual bool Shutdown();

	void SetApplicationSettings( const ApplicationSettings& settings );
	ApplicationSettings& GetApplicationSettings();
	void SetPhyxSettings( const PhyxSettings& settings );
	PhyxSettings& GetPhyxSettings();
	void SetGameSettings( const GameSettings& settings );
	GameSettings& GetGameSettings();

private:

	ApplicationSettings applicationSettings;
	PhyxSettings physicsSettings;
	GameSettings gameSettings;
};

#endif //_WORLDSETIINGS_H
