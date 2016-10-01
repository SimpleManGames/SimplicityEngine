#ifndef _SHADERDATASOURCE_H
#define _SHADERDATASOURCE_H

#include "Shader.h"

class ShaderDataSource {
public:
	ShaderDataSource() {}
	virtual ~ShaderDataSource() {}
	virtual ShaderLoadStatus LoadSharedSource( const char * sharedVertexData, const char * sharedFragmentData ) = 0;
	virtual ShaderLoadStatus LoadShaderSource( const char * name, const char * vertexShaderData, const char * fragmentShaderData ) = 0;

private:
	ShaderDataSource( const ShaderDataSource * orig );
	ShaderDataSource & operator = ( const ShaderDataSource & other );
};

#endif // !_SHADERDATASOURCE_H