#ifndef _RESOURCEMANAGER_H
#define _RESOURCEMANAGER_H

#include <map>

#include "Helpers\Manager.h"

#include "Defines\texture.h"
#include "Core\Rendering\Shader.h"
#include "Defines\geometry.h"
#include "Defines\framebuffer.h"
#include "Defines\vertex.h"

#include "Helpers\Singleton.h"
#include "Diagnostics\Logger.h"

class ResourceManager : Manager {
private:
	std::map<const char *, Geometry> objects;
	std::map<const char *, Shader> shaders;
	std::map<const char *, Texture> textures;
	std::map<const char *, Framebuffer> framebuffers;

public:
	ResourceManager();
	~ResourceManager();

	// Inherited via Manager
	virtual bool Initialize();
	// Inherited via Manager
	virtual bool Shutdown();

	template<typename T>
	bool Add( const char * name, const char * p );

	// Add Function for Shaders
	// Returns true if we successfully added the shader to the shaders map
	bool Add( const char * name, const char * v, const char * f );
	// Add Function for Framebuffers
	// Returns true if we successfully added the framebuffer to the framebuffer map
	bool Add( const char * name, const size_t width, const size_t height, const size_t colors );

	template<typename T>
	T Get( const char * name );
};

#endif // !_RESOURCEMANAGER_H

#include "Helpers\TypeChecker.h"

template<typename T>
inline bool ResourceManager::Add( const char * name, const char * p ) {
	if( TypeChecker::eqTypes<T, Geometry>() ) {
		objects[ name ] = Geometry_Internal::Load( p );
		return true;
	}
	if( TypeChecker::eqTypes<T, Texture>() ) {
		textures[ name ] = Texture_Internal::Load( p );
		return true;
	}
	Singleton<Logger>::GetInstance().Log( _T( "Template call is only needed for Geometry and Texture objects" ), LOGTYPE_WARNING );
	return false;
}

template<typename T>
inline T ResourceManager::Get( const char * name ) {
	if( TypeChecker::eqTypes<T, Geometry>() ) return objects[ name ];
	if( TypeChecker::eqTypes<T, Texture>() ) return textures[ name ];
	if( TypeChecker::eqTypes<T, Shader>() ) return shaders[ name ];
	if( TypeChecker::eqTypes<T, Framebuffer>() ) return framebuffers[ name ];

	Singleton<Logger>::GetInstance().Log( _T( "Couldn't find type as per requested, returning the default constructor for type" ), LOGTYPE_WARNING );
	return T();
}