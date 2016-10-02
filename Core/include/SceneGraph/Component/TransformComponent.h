#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H

#include <GLM/glm.hpp>
#include <GLM/gtc/quaternion.hpp>

#include "SceneGraph\Component\Component.h"

class TransformComponent : public Component {
public :
	explicit TransformComponent();
	~TransformComponent( void );

	glm::mat4 GetLocalTransform();
	glm::mat4 GetLocalTransformInverse();
	
	glm::mat4 GetGlobalTransform();
	glm::mat4 GetGlobalTransformInverse();

	glm::vec3 GetPosition() const;
	glm::vec3 GetScale() const;
	glm::quat GetRotation() const;

	void SetPosition( const glm::vec3 & newPosition );
	void SetRotation( const glm::quat & quaternion );
	void SetRotation( const glm::vec3 & euler );
	void SetScale( const glm::vec3 & scale );

private:
	TransformComponent( const TransformComponent & orig );
	TransformComponent & operator = ( const TransformComponent & );

	void UpdateIfDirty();
	void UpdateInverseIfDirty();
	void UpdateGlobalIfDirty();
	void UpdateGlobalInverseIfDirty();

	void SetGlobalDirtyFlag();
	void SetLocalDirty();

	bool dirtyFlag;
	bool dirtyFlagInverse;
	bool dirtyFlagGlobal;
	bool dirtyFlagGlobalInverse;

	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	glm::mat4 localTransform;
	glm::mat4 localTransformInverse;
	glm::mat4 globalTransform;
	glm::mat4 globalTransformInverse;
};

#endif // !_TRANSFORMCOMPONENT_H