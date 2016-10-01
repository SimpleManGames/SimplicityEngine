#ifndef _MATERIAL_H

#include <vector>

#include "GLM\glm.hpp"

#include "Core\Rendering\Base\TextureBase.h"

#include "SceneGraph\Component\Component.h"

#include "Core\Rendering\Shader.h"
#include "Defines\texture.h"

class Camera;

enum ShaderParamType { 
	SPT_FLOAT,
	SPT_VECTOR2,
	SPT_VECTOR3,
	SPT_VECTOR4,
	SPT_INT,
	SPT_TEXTURE,
	SPT_SHADOW_SETUP,
	SPT_SHADER_SETUP_NAME
};

struct ShaderParameters {
	int id;
	ShaderParamType paramType;
	union ShaderValue {
		float f[ 4 ];
		int integer[ 2 ];
		Camera *camera;
		char *cameraChar;
	} shaderValue;
};

class Material : public Component {
public:
	Material( Shader * shader );
	virtual ~Material();
	void Bind();

	bool SetVector2( const char * name, glm::vec2 vec );
	bool SetVector3( const char * name, glm::vec3 vec );
	bool SetVector4( const char * name, glm::vec4 vec );
	bool SetFloat( const char * name, float f );
	bool SetTexture( const char * name, TextureBase * texture );
	bool SetInt( const char * name, int i );
	bool SetShadowSetup( const char * name, const char * cameraName );
	
	void SetName( const char * name ) { this->name = name; }
	// Create a copy of the material
	Material * Instance();
private:
	Material( const Material& orig ); // Disallows the copy constructor
	Material& operator = ( const Material& other ); // Disallows the copy constructor

	void AddParameter( ShaderParameters & param );

	Shader * shader;
	std::vector<TextureBase*> textures;
	const char * name;
	std::vector<ShaderParameters> parameters;
};

#endif // !_MATERIAL_H
