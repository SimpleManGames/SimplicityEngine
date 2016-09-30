#include "Core\Rendering\Material.h"

Material::Material( Shader * shader ) {}

Material::~Material() {}

void Material::Bind() {}

bool Material::SetVector2( const char * name, glm::vec2 vec ) {
	return false;
}

bool Material::SetVector3( const char * name, glm::vec3 vec ) {
	return false;
}

bool Material::SetVector4( const char * name, glm::vec4 vec ) {
	return false;
}

bool Material::SetFloat( const char * name, float f ) {
	return false;
}

bool Material::SetTexture( const char * name, TextureBase * texture ) {
	return false;
}

bool Material::SetInt( const char * name, int i ) {
	return false;
}

bool Material::SetShadowSetup( const char * name, const char * cameraName ) {
	return false;
}

Material * Material::Instance() {
	return nullptr;
}

void Material::AddParameter( ShaderParameters & param ) {}
