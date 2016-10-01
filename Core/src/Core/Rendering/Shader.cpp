#include "Core\Rendering\Shader.h"

#include <string>

#include "GLEW\glew.h"

#include "Diagnostics\Logger.h"
#include "Helpers\Singleton.h"
#include "Core\Rendering\ShaderDataSource.h"

Shader * Shader::CreateShader( const char * name, const char * shaderName, ShaderDataSource * shaderDataSource, ShaderLoadStatus & outLoadStatus ) {
	Shader * shader = new Shader( shaderName, name, shaderDataSource );
	outLoadStatus = shader->Reload();
	if( outLoadStatus != Shader_OK ) {
		Singleton<Logger>::GetInstance().Log( _T( "shader->Reload() failed for " + ToWString( shaderName ) ), LOGTYPE_ERROR );
		delete shader;
		return NULL;
	}
	return shader;
}

Shader::Shader( const char * shaderName, const char * assetName, ShaderDataSource * shaderDataSource )
	: shaderProgramId( 0 )
	, vertexShaderId( 0 )
	, fragmentShaderId( 0 )
	, shaderName( shaderName )
	, assetName( assetName )
	, shaderDataSource( shaderDataSource ) {

}
Shader::~Shader() {
	Unload();
}

void checkInfoLogShader( unsigned int shaderId ) {
	int infoLogLength;
	glGetShaderiv( shaderId, GL_INFO_LOG_LENGTH, &infoLogLength );
	if( infoLogLength > 0 ) {
		char * infoLog = new char[ infoLogLength + 1 ];
		glGetShaderInfoLog( shaderId, infoLogLength, &infoLogLength, infoLog );
		Singleton<Logger>::GetInstance().Log( _T( "Shader Log Info: " + ToWString( infoLog ) ), LOGTYPE_INFO );
		delete[ ]infoLog;
	}
}

void Shader::Bind() {
	glUseProgram( shaderProgramId );
}

ShaderLoadStatus Shader::Reload() {
	Unload();
	const char * sharedVertexData = {};
	const char * sharedFragmentData = {};
	if( strlen( sharedVertexData ) == 0 || strlen( sharedFragmentData ) == 0 ) {
		shaderDataSource->LoadSharedSource( sharedVertexData, sharedFragmentData );
	}

	const char * vertexData = {};
	const char * fragmentData = {};
	ShaderLoadStatus loadStatus = shaderDataSource->LoadShaderSource( assetName, vertexData, fragmentData );
	if( loadStatus != Shader_OK )
		return loadStatus;
	loadStatus = CompileAndLink( sharedVertexData, sharedFragmentData, vertexData, fragmentData );
	return loadStatus;
}

void Shader::Unload() {
	if( fragmentShaderId != 0 ) {
		glDeleteShader( fragmentShaderId );
		fragmentShaderId = 0;
	}
	if( vertexShaderId != 0 ) {
		glDeleteShader( vertexShaderId );
		vertexShaderId = 0;
	}
	if( shaderProgramId != 0 ) {
		glDeleteProgram( shaderProgramId );
		shaderProgramId = 0;
	}
}

int Shader::GetUniformLocation( const char * location ) {
	return glGetUniformLocation( shaderProgramId, location );
}


ShaderLoadStatus Shader::CompileAndLink( const char * sharedVertexData, const char * sharedFragmentData, const char * vertexData, const char * fragmentData ) {
	ShaderLoadStatus status = Compile( sharedVertexData, sharedFragmentData, vertexData, fragmentData );
	if( status != Shader_OK ) return status;
	status = Link();
	return status;
}

ShaderLoadStatus Shader::Compile( const char * sharedVertexData, const char * sharedFragmentData, const char * vertexData, const char * fragmentData ) {
	vertexShaderId = glCreateShader( GL_VERTEX_SHADER );
	fragmentShaderId = glCreateShader( GL_FRAGMENT_SHADER );

	using namespace std;
	string vShader;
	string fShader;

	vShader.append( sharedVertexData );
	vShader.append( vertexData );

	fShader.append( sharedFragmentData );
	fShader.append( fragmentData );

	unsigned int shaderIds[ 4 ] = {
		vertexShaderId,
		fragmentShaderId
	};

	const char * shaderSource[ ] = {
		vShader.c_str(),
		fShader.c_str()
	};

	const char * shaderSourceName[ ]{
		"vertexShaderSource", "fragmentShaderSource",
	};

	for( int i = 0; i < 2; i++ ) {
		if( shaderIds[ i ] == 0 )
			return Shader_Cannot_Allocate;
		glShaderSource( shaderIds[ i ], 1, &( shaderSource[ i ] ), NULL );

		int compileStatus = 0;
		glCompileShader( shaderIds[ i ] );
		glGetShaderiv( shaderIds[ i ], GL_COMPILE_STATUS, &compileStatus );
		checkInfoLogShader( shaderIds[ i ] );
		if( !compileStatus ) {
			Singleton<Logger>::GetInstance().Log( _T( "Cannot compile shader " + ToWString( shaderSourceName[ i ] ) ), LOGTYPE_ERROR );
			return Shader_Compile_Error_Vertex_Shader;
		}
	}
	return Shader_OK;
}

void checkInfoLogProgram( unsigned int programId ) {
	int infoLogLength;
	glGetProgramiv( programId, GL_INFO_LOG_LENGTH, &infoLogLength );
	if( infoLogLength > 0 ) {
		char * infoLog = new char[ infoLogLength + 1 ];
		glGetProgramInfoLog( programId, infoLogLength, &infoLogLength, infoLog );
		Singleton<Logger>::GetInstance().Log( _T( "Program Info Log: " + ToWString( infoLog ) ), LOGTYPE_INFO );
		delete[ ]infoLog;
	}
}

ShaderLoadStatus Shader::Link() {
	shaderProgramId = glCreateProgram();

	if( shaderProgramId == 0 ) return Shader_Cannot_Allocate;

	glAttachShader( shaderProgramId, vertexShaderId );
	glAttachShader( shaderProgramId, fragmentShaderId );

	glLinkProgram( shaderProgramId );
	checkInfoLogProgram( shaderProgramId );

	int linkStatus = 0;
	glGetProgramiv( shaderProgramId, GL_LINK_STATUS, &linkStatus );
	if( !linkStatus ) {
		Singleton<Logger>::GetInstance().Log( _T( "Link Error" ), LOGTYPE_ERROR );
		return Shader_Link_Error;
	}
	return Shader_OK;
}
