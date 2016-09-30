#include "Core\Rendering\Material.h"

#include "Diagnostics\Logger.h"
#include "Helpers\Singleton.h"

#include "GLEW\glew.h"

void Material::SetInt( const char * uniformName, int value ) {
	if( uniforms.intUniforms.find( uniformName ) == uniforms.intUniforms.end() )
		uniforms.intUniforms[ uniformName ] = value;
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform already exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

void Material::SetFloat( const char * uniformName, float value ) {
	if( uniforms.floatUniforms.find( uniformName ) == uniforms.floatUniforms.end() )
		uniforms.floatUniforms[ uniformName ] = value;
	else
		Singleton<Logger>::GetInstance().Log( _T( "Shader float uniform already exists " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

void Material::SetVec3( const char * uniformName, glm::vec3 value ) {
	if( uniforms.vec3Uniforms.find( uniformName ) == uniforms.vec3Uniforms.end() )
		uniforms.vec3Uniforms[ uniformName ] = value;
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform already exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

void Material::SetMat4( const char * uniformName, glm::mat4 value ) {
	if( uniforms.mat4Uniforms.find( uniformName ) == uniforms.mat4Uniforms.end() )
		uniforms.mat4Uniforms[ uniformName ] = value;
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform already exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

void Material::SetTexture( const char * uniformName, Texture value ) {
	if( uniforms.textureUniforms.find( uniformName ) == uniforms.textureUniforms.end() )
		uniforms.textureUniforms[ uniformName ] = value;
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform already exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

void Material::SetArray( const char * uniformName, float value[ 16 ] ) {
	if( uniforms.floatArrayUniforms.find( uniformName ) == uniforms.floatArrayUniforms.end() )
		uniforms.floatArrayUniforms[ uniformName ] = value;
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform already exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

int Material::GetInt( const char * uniformName ) {
	if( uniforms.intUniforms.find( uniformName ) != uniforms.intUniforms.end() )
		return uniforms.intUniforms[ uniformName ];
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform doesn't exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

float Material::GetFloat( const char * uniformName ) {
	if( uniforms.floatUniforms.find( uniformName ) != uniforms.floatUniforms.end() )
		return uniforms.floatUniforms[ uniformName ];
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform doesn't exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

glm::vec3 Material::GetVec3( const char * uniformName ) {
	if( uniforms.vec3Uniforms.find( uniformName ) != uniforms.vec3Uniforms.end() )
		return uniforms.vec3Uniforms[ uniformName ];
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform doesn't exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

glm::mat4 Material::GetMat4( const char * uniformName ) {
	if( uniforms.mat4Uniforms.find( uniformName ) != uniforms.mat4Uniforms.end() )
		return uniforms.mat4Uniforms[ uniformName ];
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform doesn't exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

Texture Material::GetTexture( const char * uniformName ) {
	if( uniforms.textureUniforms.find( uniformName ) != uniforms.textureUniforms.end() )
		return uniforms.textureUniforms[ uniformName ];
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform doesn't exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

float * Material::GetArray( const char * uniformName ) {
	if( uniforms.floatArrayUniforms.find( uniformName ) != uniforms.floatArrayUniforms.end() )
		return uniforms.floatArrayUniforms[ uniformName ];
	else
		Singleton<Logger>::GetInstance().Log( _T( "Uniform doesn't exists: " + ToWString( uniformName ) ), LOGTYPE_WARNING );
}

bool Material::BuildMaterial() {
	
	unsigned int count = 0;

	for each( auto uni in uniforms.intUniforms ) {
		glUniform1i( count, uni.second );
	}

	for each( auto uni in uniforms.floatUniforms ) {
		glUniform1f( count, uni.second );
	}

	
}
