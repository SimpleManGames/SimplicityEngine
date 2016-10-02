#include "SceneGraph\Component\TransformComponent.h"

#include <algorithm>

#include "GLM\gtc\matrix_transform.hpp"
#include "GLM\gtx\euler_angles.hpp"

#include "SceneGraph\Object\GameObjects\GameObject.h"

TransformComponent::TransformComponent()
	: dirtyFlag( false ), dirtyFlagInverse( false ), dirtyFlagGlobal( false ), dirtyFlagGlobalInverse( false ),
	scale( 1, 1, 1 ), rotation( glm::quat( 0.0f, 0.0f, 0.0f, 0.0f ) ) {}

TransformComponent::~TransformComponent( void ) {}

glm::mat4 TransformComponent::GetLocalTransform() {
	UpdateIfDirty();
	return localTransform;
}
glm::mat4 TransformComponent::GetLocalTransformInverse() {
	UpdateInverseIfDirty();
	return localTransformInverse;
}
glm::mat4 TransformComponent::GetGlobalTransform() {
	if( GetParent()->GetComponent<TransformComponent>() == NULL )
		return GetLocalTransform();
	UpdateGlobalIfDirty();
	return globalTransform;
}
glm::mat4 TransformComponent::GetGlobalTransformInverse() {
	if( GetParent()->GetComponent<TransformComponent>() == NULL )
		return GetLocalTransformInverse();
	UpdateGlobalInverseIfDirty();
	return globalTransformInverse;
}
glm::vec3 TransformComponent::GetPosition() const { return position; }
glm::vec3 TransformComponent::GetScale() const { return scale; }
glm::quat TransformComponent::GetRotation() const { return rotation; }

void TransformComponent::SetPosition( const glm::vec3 & newPosition ) {
	position = newPosition;
	SetLocalDirty();
}
void TransformComponent::SetRotation( const glm::quat & quaternion ) {
	this->rotation = quaternion;
	SetLocalDirty();
}
void TransformComponent::SetRotation( const glm::vec3 & euler ) {
	float pitch = euler[ 0 ], yaw = euler[ 1 ], roll = euler[ 2 ];
	float cX, cY, cZ, sX, sY, sZ, cYcZ, sYsZ, cYsZ, sYcZ;

	pitch *= 0.5f;
	yaw *= 0.5f;
	roll *= 0.5f;

	cX = cos(pitch);
	cY = cos(yaw);
	cZ = cos(roll);

	sX = sin(pitch);
	sY = sin(yaw);
	sZ = sin(roll);

	cYcZ = cY * cZ;
	sYsZ = sY * sZ;
	cYsZ = cY * sZ;
	sYcZ = sY * cZ;

	rotation.w = cX * cYcZ + sX * sYsZ;
	rotation.x = sX * cYcZ - cX * sYsZ;
	rotation.y = cX * sYcZ + sX * cYsZ;
	rotation.z = cX * cYsZ - sX * sYcZ;

	SetLocalDirty();
}
void TransformComponent::SetScale( const glm::vec3 & scale ) {
	this->scale = scale;
	SetLocalDirty();
}

void TransformComponent::UpdateIfDirty() {
	if( dirtyFlag ) {
		// translate * scale * rotate
		localTransform =
			glm::mat4( glm::vec4( 1, 0, 0, 0 ),
					   glm::vec4( 0, 1, 0, 0 ),
					   glm::vec4( 0, 0, 1, 0 ),
					   glm::vec4( position, 1 )
			);
		localTransform = glm::scale( localTransform, scale );
		localTransform = localTransform * glm::mat4_cast( rotation );
		dirtyFlag = false;
	}
}

void TransformComponent::UpdateInverseIfDirty() {
	if( dirtyFlagInverse ) {
		// rotate ^ -1 * scale ^ 1 * translate ^ -1
		localTransformInverse = glm::transpose( glm::mat4_cast( rotation ) );
		localTransformInverse = glm::scale( localTransformInverse, 1.0f / scale );
		localTransformInverse = glm::translate( localTransformInverse, -position );
		dirtyFlagInverse = false;
	}
}

void TransformComponent::UpdateGlobalIfDirty() {
	if( dirtyFlagGlobal ) {
		if( GetParent() != NULL ) {
			GetParent()->GetComponent<TransformComponent>()->UpdateGlobalIfDirty();
			globalTransform = GetLocalTransform() * GetParent()->GetComponent<TransformComponent>()->GetGlobalTransform();
		}
		dirtyFlagGlobalInverse = false;
	}
}

void TransformComponent::UpdateGlobalInverseIfDirty() {
	if( dirtyFlagGlobalInverse ) {
		if( GetParent() != NULL ) {
			GetParent()->GetComponent<TransformComponent>()->UpdateGlobalInverseIfDirty();
			globalTransformInverse = GetLocalTransformInverse() * GetParent()->GetComponent<TransformComponent>()->GetGlobalTransformInverse();
		}
		dirtyFlagGlobalInverse = false;
	}
}

void TransformComponent::SetGlobalDirtyFlag() {
	dirtyFlagGlobal = true;
	dirtyFlagGlobalInverse = true;
	std::vector<TransformComponent *> children = GetParent()->GetComponentsOfType<TransformComponent>();
	std::vector<TransformComponent *>::iterator iter = children.begin();
	for( ; iter != children.end(); iter++ )
		( *iter )->SetGlobalDirtyFlag();
}

void TransformComponent::SetLocalDirty() {
	dirtyFlag = true;
	dirtyFlagInverse = true;
	SetGlobalDirtyFlag();
}
