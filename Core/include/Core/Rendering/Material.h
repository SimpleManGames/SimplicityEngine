#ifndef _MATERIAL_H

#include <map>

#include "GLM\glm.hpp"

#include "Defines\shader.h"
#include "Defines\texture.h"

namespace Material_Internal {
	struct ShaderUniforms {
		std::map<const char *, int> intUniforms;
		std::map<const char *, float> floatUniforms;
		std::map<const char *, glm::vec3> vec3Uniforms;
		std::map<const char *, glm::mat4> mat4Uniforms;
		std::map<const char *, Texture> textureUniforms;
		std::map<const char *, float * > floatArrayUniforms;
	};
}

class Material {
public:
	Material() : shader( { 0 } ) {}
	Material( Shader s ) : shader( s ) {}
	Material( const char * vertShader, const char * fragShader ) {
		shader = Shader_Internal::Make( vertShader, fragShader );
	}

public:
	void SetInt( const char * uniformName, int value );
	void SetFloat( const char * uniformName, float value );
	void SetVec3( const char * uniformName, glm::vec3 value );
	void SetMat4( const char * uniformName, glm::mat4 value );
	void SetTexture( const char * uniformName, Texture value );
	void SetArray( const char * uniformName, float value[ 16 ] );

	int GetInt( const char * uniformName );
	float GetFloat( const char * uniformName );
	glm::vec3 GetVec3( const char * uniformName );
	glm::mat4 GetMat4( const char * uniformName );
	Texture GetTexture( const char * uniformName );
	float * GetArray( const char * uniformName );

	/// Use this during the draw call to construct the shader
	bool BuildMaterial();

	operator bool() const { return shader; }

private:
	
	Shader shader;
	Material_Internal::ShaderUniforms uniforms;
};

#endif // !_MATERIAL_H
