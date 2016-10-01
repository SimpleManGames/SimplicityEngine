#include "Core\Rendering\ShaderFileDataSource.h"

#include <sstream>
#include <fstream>

#include "Diagnostics\Logger.h"
#include "Helpers\Singleton.h"

ShaderFileDataSource::ShaderFileDataSource() {}

ShaderFileDataSource::~ShaderFileDataSource() {}

ShaderLoadStatus ShaderFileDataSource::LoadSharedSource( const char * sharedVertexData, const char * sharedFragmentData ) {
	const char * fileEndings[ 2 ] = { ".vert", ".frag" };
	std::string * sources[ 2 ] = { ( std::string * )sharedVertexData, ( std::string * )sharedFragmentData };

	for( unsigned int i = 0; i < 2; i++ ) {
		const char * fileName( "res/shader" );
		fileName = new char[ strlen( fileName ) + strlen( fileEndings[ i ] ) + 1 ];
		std::ifstream input( fileName );

		std::stringstream oss;
		oss << input.rdbuf();
		*( sources[ i ] ) = oss.str();
		input.close();

		if( input.fail() ) {
			std::stringstream ss;
			Singleton<Logger>::GetInstance().Log( _T( "Cannot load " + ToWString( fileName ) ), LOGTYPE_ERROR );
			delete[ ] fileName;
			return Shader_File_Not_Found;
		}
		delete[ ] fileName;
	}
	return Shader_OK;
}

ShaderLoadStatus ShaderFileDataSource::LoadSharedSource( const char * name, const char * vertexShaderData, const char * fragmentShaderData ) {
	const char * fileEndings[ 2 ] = { ".vert", ".frag" };
	std::string * sources[ 2 ] = { ( std::string * )vertexShaderData, ( std::string * )fragmentShaderData };

	for( unsigned int i = 0; i < 2; i++ ) {
		const char * fileName( "res/shader" );
		fileName = new char[ strlen( fileName ) + strlen( name ) + strlen( fileEndings[ i ] ) + 1 ];
		std::ifstream input( fileName );

		std::stringstream oss;
		oss << input.rdbuf();
		*( sources[ i ] ) = oss.str();
		input.close();

		if( input.fail() ) {
			std::stringstream ss;
			Singleton<Logger>::GetInstance().Log( _T( "Cannot load" ) + ToWString( fileName ), LOGTYPE_ERROR );
			delete[ ] fileName;
			return Shader_File_Not_Found;
		}
		delete[ ] fileName;
	}
	return Shader_OK;
}