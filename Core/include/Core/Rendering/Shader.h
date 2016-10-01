#ifndef _SHADER_H
#define _SHADER_H

class ShaderDataSource;

enum ShaderLoadStatus {
	Shader_OK,
	Shader_Cannot_Allocate,
	Shader_File_Not_Found,
	Shader_Compile_Error_Vertex_Shader,
	Shader_Compile_Error_Fragment_Shader,
	Shader_Link_Error
};

class Shader {
public :
	static Shader *CreateShader( const char * name, const char * shaderName, ShaderDataSource * shaderDataSource, ShaderLoadStatus & outLoadStatus );
	virtual ~Shader();

	void Bind();

	ShaderLoadStatus Reload();
	void Unload();
	const char * GetShaderName() { return shaderName; }
	int GetUniformLocation( const char * location );
	
	void IncreaseUsageCount() { usageCount++; }
	void DecreaseUsageCount() { usageCount--; }
	int GetUsageCount() { return usageCount; }
private:
	Shader( const char * shaderName, const char * assetName, ShaderDataSource * shaderDataSource );
	ShaderLoadStatus CompileAndLink( const char * sharedVertexData, const char * sharedFragmentData,
									 const char * vertexData, const char * fragmentData );
	ShaderLoadStatus Compile( const char * sharedVertexData, const char * sharedFragmentData,
							  const char * vertexData, const char * fragmentData );
	ShaderLoadStatus Link();

	Shader( const Shader& orig ); // Disallow copy constructor
	Shader& operator = ( const Shader & other );

	unsigned int shaderProgramId;
	unsigned int vertexShaderId;
	unsigned int fragmentShaderId;

	int usageCount;
	const char * shaderName;
	const char * assetName;
	ShaderDataSource * shaderDataSource;
};

#endif // !_SHADER_H
