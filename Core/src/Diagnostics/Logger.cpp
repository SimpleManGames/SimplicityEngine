#include "Diagnostics/Logger.h"

#ifndef _WINDOWS_
#include <Windows.h>
#endif

#include "Defines/stringstream.h"
#include "Defines/iostream.h"
#include "Defines/fstream.h"
#include "Defines/assert.h"

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

Logger::Logger( void ) {}
Logger::~Logger( void ) {}

bool Logger::Initialize() {
	return true;
}
bool Logger::Shutdown() {
	this->logMessages.clear();
	return true;
}

void Logger::Log( const std::tstring& Message, LogType type, int ln, const std::tstring& fn ) {
	std::tstringstream buffer;

	switch( type ) {
		case LogType::INFO_LOG:

			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), WHITE );
			buffer << _T( "Info Message" ) << _T( " INFO: " ) << Message.c_str();
			buffer << _T( "\nFound in file: " ) << fn;
			buffer << _T( "\nAt linenumber: " ) << ln;
			buffer << _T( "\n" );

			this->logMessages.push_back( LogData( LogType::INFO_LOG, buffer.str() ) );

			std::tcout << _T( "INFO: " ) << Message.c_str() << std::endl;
			OutputDebugString( buffer.str().c_str() );

			break;
		case LogType::WARNING_LOG:

			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), YELLOW );
			buffer << _T( "Warning Message" ) << _T( " WARNING: " ) << Message.c_str();
			buffer << _T( "\nFound in file: " ) << fn;
			buffer << _T( "\nAt linenumber: " ) << ln;
			buffer << _T( "\n" );

			this->logMessages.push_back( LogData( LogType::WARNING_LOG, buffer.str() ) );

			std::tcout << _T( "WARNING: " ) << Message.c_str() << std::endl;
			OutputDebugString( buffer.str().c_str() );

			break;
		case LogType::ERROR_LOG:

			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), RED );
			buffer << _T( "Error Message" ) << _T( " ERROR: " ) << Message.c_str();
			buffer << _T( "\nFound in file: " ) << fn;
			buffer << _T( "\nAt linenumber: " ) << ln;
			buffer << _T( "\n" );

			this->logMessages.push_back( LogData( LogType::ERROR_LOG, buffer.str() ) );

			std::tcout << _T( "ERROR: " ) << Message.c_str() << std::endl;
			OutputDebugString( buffer.str().c_str() );

			break;
		case LogType::TODO_LOG:

			SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), LIGHTCYAN );
			buffer << _T( "Todo Message" ) << _T( " TODO: " ) << Message.c_str();
			buffer << _T( "\nFound in file: " ) << fn;
			buffer << _T( "\nAt linenumber: " ) << ln;
			buffer << _T( "\n" );

			this->logMessages.push_back( LogData( LogType::TODO_LOG, buffer.str() ) );

			std::tcout << _T( "TODO: " ) << Message.c_str() << std::endl;
			OutputDebugString( buffer.str().c_str() );

			break;
	}

	buffer.clear();
	buffer.str( _T( "" ) );
}

void Logger::WriteLogFile() {
	int currentlog = 0;
	for( LogData& logdata : this->logMessages ) {
		std::tstringstream buffer;
		buffer << ".\\Logs\\" << _T( "LogFile" ) << currentlog << _T( ".txt" ) << _T( "\0" );

		std::tofstream logfile( buffer.str().c_str(), std::ios::in | std::ios::out | std::ios::trunc );

		if( !logfile ) {
			OutputDebugString( _T( "Cannot create log file \n" ) );
			return;
		}

		logfile << _T( "Logfile " ) << currentlog << std::endl;
		logfile << __DATE__ << _T( " " ) << __TIME__ << std::endl;
		logfile << logdata.ToString() << std::endl;
		logfile << _T( "End of log" );

		logfile.close();

		++currentlog;
	}
}

const std::tstring LogData::ToString() {
	std::tstringstream buffer;

	switch( type ) {
		case LogType::INFO_LOG:
			buffer << _T( "LogMessage Type: Info" ) << std::endl;
			break;
		case LogType::WARNING_LOG:
			buffer << _T( "LogMessage Type: Warning" ) << std::endl;
			break;
		case LogType::ERROR_LOG:
			buffer << _T( "LogMessage Type: Error" ) << std::endl;
			break;
		case LogType::TODO_LOG:
			buffer << _T( "LogMessage Type: ToDo" ) << std::endl;
			break;
		default:
			buffer << _T( "LogMessage Type: Not supported" ) << std::endl;
			break;
	}

	buffer << message << std::endl;
	return buffer.str();
}
