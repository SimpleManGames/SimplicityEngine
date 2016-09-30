#ifndef _SHADER_H
#define _SHADER_H

struct Shader {
	unsigned handle = -1;

	operator bool() const { return handle != -1; }

	template<typename T>
	operator T() { return T(); }
};

namespace Shader_Internal {
	namespace Shader_Defaults {
		static const char *  vert = "#version 150\n" "in vec4 position;" "void main() { gl_Position = position; }";
		static const char * frag = "#version 150\n" "out vec4 outColor;" "void main() { outColor = gl_Position; }";
	}

	Shader Make( const char * vert, const char * frag );
	Shader Load( const char * vPath, const char * fPath );
	void Free( Shader & s );
}

#endif // !_SHADER_H