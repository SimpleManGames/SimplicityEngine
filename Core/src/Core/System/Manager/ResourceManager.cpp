#include "Core\System\Manager\ResourceManager.h"


ResourceManager::ResourceManager() {}
ResourceManager::~ResourceManager() {}

bool ResourceManager::Initialize() {
	return true;
}

bool ResourceManager::Shutdown() {
	for each( auto s in shaders ) Shader_Internal::Free( s.second );
	for each( auto g in objects ) Geometry_Internal::Free( g.second );
	for each( auto t in textures ) Texture_Internal::Free( t.second );
	for each( auto f in framebuffers ) Framebuffer_Internal::Free( f.second );
	
	return true;
}

//bool ResourceManager::Add( const char * name, const Vertex * verts, const size_t vSize, const unsigned * tris, const size_t tSize ) {
//	objects[ name ] = Geometry_Internal::Make( verts, vSize, tris, tSize );
//	return true;
//}

bool ResourceManager::Add( const char * name, const char * v, const char * f ) {
	shaders[ name ] = Shader_Internal::Make( v, f );
	return true;
}

//bool ResourceManager::Add( const char * name, const char * p ) {
//	textures[ name ] = Texture_Internal::Load( p );
//	return true;
//}

bool ResourceManager::Add( const char * name, const size_t width, const size_t height, const size_t colors ) {
	framebuffers[ name ] = Framebuffer_Internal::Make( width, height, colors );
	return true;
}