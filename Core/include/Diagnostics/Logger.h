#ifndef _LOGGER_H
#define _LOGGER_H

#include "Helpers/Manager.h"

#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _STRING_H
#include "Defines/string.h"
#endif
#ifndef _LOGTYPE_H
#include "Defines/Types/LogType.h"
#endif

struct LogData {
	LogData( LogType t, const std::tstring& m )
		: type( t )
		, message( m ) {}

	const std::tstring ToString();

	LogType type;
	std::tstring message;
};

#define LOGTYPE_INFO LogType::INFO_LOG,__LINE__,__FILEW__
#define LOGTYPE_WARNING LogType::WARNING_LOG,__LINE__,__FILEW__
#define LOGTYPE_ERROR LogType::ERROR_LOG,__LINE__,__FILEW__
#define LOGTYPE_TODO LogType::TODO_LOG,__LINE__,__FILEW__

class Logger : public Manager {
public:
	Logger( void );
	virtual ~Logger( void );

	bool Initialize();
	bool Shutdown();

	void Log( const std::tstring& Message, LogType type, int ln, const std::tstring& fn );
	void WriteLogFile();

private:
	Logger( const Logger& tRef );
	const Logger& operator=( const Logger& tRef );

	std::vector<LogData> logMessages;
};

inline std::tstring ToWString( const std::string &s ) {
	std::tstring wsTmp( s.begin(), s.end() );
	return wsTmp;
}

inline std::tstring ToWString( const char * s ) {
	return ToWString( std::string( s ) );
}

#endif