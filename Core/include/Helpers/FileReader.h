#ifndef _FILEREADER_H
#define _FILEREADER_H

#include <string>
#include <fstream>

#include "Helpers\Singleton.h"
#include "Diagnostics\Logger.h"

char * GetStringFromFile( const char * path ) {
	unsigned int array_size = 5012;
	char * array = new char[ array_size ];
	unsigned int position = 0;
	
	std::fstream fin( path );

	if( fin.is_open() ) {
		while( !fin.eof() && position < array_size ) {
			fin.get( array[ position ] );
			position++;
		}
		array[ position - 1 ] = '\0';
	} else {
		Singleton<Logger>::GetInstance().Log( _T( "File could not be opened" ), LOGTYPE_ERROR );
		return nullptr;
	}
	return array;
}

#endif // !_FILEREADER_H