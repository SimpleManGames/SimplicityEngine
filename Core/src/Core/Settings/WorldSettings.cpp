#include "Core/Settings/WorldSettings.h"

WorldSettings::WorldSettings()
	:applicationSettings()
	, physicsSettings()
	, gameSettings() {}
WorldSettings::~WorldSettings() {}

bool WorldSettings::Initialize() {
	applicationSettings.Initialize( _T( "resources/INI/Engine.ini" ) );
	physicsSettings.Initialize( _T( "resources/INI/Engine.ini" ) );
	gameSettings.Initialize( _T( "resources/INI/Engine.ini" ) );

	return true;
}
bool WorldSettings::Shutdown() { return true; }

void WorldSettings::SetApplicationSettings( const ApplicationSettings& settings ) { this->applicationSettings = settings; }
ApplicationSettings& WorldSettings::GetApplicationSettings() { return this->applicationSettings; }
void WorldSettings::SetPhyxSettings( const PhyxSettings& settings ) { this->physicsSettings = settings; }
PhyxSettings& WorldSettings::GetPhyxSettings() { return this->physicsSettings; }
void WorldSettings::SetGameSettings( const GameSettings& settings ) { this->gameSettings = settings; }
GameSettings& WorldSettings::GetGameSettings() { return this->gameSettings; }