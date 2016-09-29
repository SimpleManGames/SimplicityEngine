#ifndef _MATERIAL_H

#include <map>
#include <string>

#include "GLM\glm.hpp"

#include "Defines\shader.h"
#include "Defines\texture.h"

namespace Material_Internal {
	struct ShaderUniforms {
		std::map<std::string, int> intUniforms;
		std::map<std::string, float> floatUniforms;
		std::map<std::string, glm::vec3 &> vec3Uniforms;
		std::map<std::string, glm::mat4 &> mat4Uniforms;
		std::map<std::string, Texture &> textureUniforms;
		std::map<std::string, float[ 16 ] > floatArrayUniforms;
	};
}

class Material {
	Material( Shader s ) : shader(s) {}
	Material( const char * vertShader, const char * fragShader ) {
		shader = Shader_Internal::Make( vertShader, fragShader );
	}


public:
	template<typename T>
	void SetUniform( std::string uniformName, T val );
	template<typename T>
	T GetUniform( std::string uniformName );

private:
	Shader shader;
	Material_Internal::ShaderUniforms shaderDetails;
};

#endif // !_MATERIAL_H

template<typename T>
inline void Material::SetUniform( std::string uniformName, T val ) {
	
}

template<typename T>
inline T Material::GetUniform( std::string uniformName ) {
	return T();
}
