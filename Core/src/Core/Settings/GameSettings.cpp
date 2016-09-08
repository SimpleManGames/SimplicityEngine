#include "Core/Settings/GameSettings.h"

GameSettings::GameSettings()
	: Settings()
	, defaultSceneName( _T( "" ) ) {}
GameSettings::~GameSettings() {}

void GameSettings::Initialize( const std::tstring& filePath ) { Settings::Initialize( filePath ); }

void GameSettings::SetDefaultSceneName( const std::tstring& name ) { this->defaultSceneName = name; }
const std::tstring& GameSettings::GetDefaultSceneName() const { return this->defaultSceneName; }

void GameSettings::ParseSettingsFile( const std::tstring& valueName, const std::tstring& valueData ) { 
	if( valueName == _T( "STARTSCENE" ) )
		SetDefaultSceneName( valueData );
}