#ifndef _SHADERFILEDATASOURCE_H
#define _SHADERFILEDATASOURCE_H

#include "Core\Rendering\ShaderDataSource.h"

class ShaderFileDataSource : public ShaderDataSource {
public:
	ShaderFileDataSource();
	virtual ~ShaderFileDataSource();
	ShaderLoadStatus LoadSharedSource( const char * sharedVertexData, const char * sharedFragmentData );
	ShaderLoadStatus LoadSharedSource( const char * name, const char * vertexShaderData, const char * fragmentShaderData );
};

#endif // !_SHADERFILEDATASOURCE_H