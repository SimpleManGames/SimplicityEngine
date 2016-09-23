#ifndef _SHADER_H
#define _SHADER_H

struct Shader {
	unsigned handle;

	template<typename T>
	operator T() { return T(); }
};

namespace Shader_Internal {
	Shader Make( const char * vert, const char * frag );
	Shader Load( const char * vPath, const char * fPath );
	void Free( Shader & s );
}

#endif // !_SHADER_H