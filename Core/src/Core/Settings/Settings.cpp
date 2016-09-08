#include "Core/Settings/Settings.h"

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _FSTREAM_H
#include "Defines/fstream.h"
#endif

#include "Helpers\Singleton.h"
#include "Diagnostics\Logger.h"

Settings::Settings() {}
Settings::~Settings() {}

void Settings::Initialize( const std::tstring& filePath ) {
	LoadFile( filePath );
}

void Settings::LoadFile( const std::tstring& filePath ) {
	std::tifstream file;
	file.open( filePath, std::ios::in );

	std::tstring line;
	if( file.is_open() ) {
		while( std::getline( file, line ) ) {
			//The description of the data
			std::tstring value_name = line.substr( 0, line.find_first_of( ':' ) );
			//Store the data that we need
			std::tstring value_data = line.substr( line.find_first_of( ':' ) + 1 );

			ParseSettingsFile( value_name, value_data );
		}
		file.close();
	} else {
		int value = GetLastError();
		Singleton<Logger>::GetInstance().Log( _T( "Could not open file: " ) + filePath, LOGTYPE_ERROR );
	}
}