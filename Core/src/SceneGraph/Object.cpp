#include "SceneGraph/Object.h"

Object::Object( const std::tstring& name )
	:active( true )

	, initialized( false )
	, destroyed( false ) {
	this->name = name == _T( "" ) ? generateName<Object>( _T( "Object_" ) ) : name;
}
Object::~Object() {}

void Object::SetInitialized() {
	this->initialized = true;
}
bool Object::GetInitialized() {
	return this->initialized;
}

void Object::Activate() {
	this->active = true;
}
void Object::Deactive() {
	this->active = false;
}
bool Object::isActive() {
	return this->active;
}

void Object::Destroy() {
	this->destroyed = true;

	this->initialized = false;
}
bool Object::isDestroyed() const {
	return this->destroyed;
}

void Object::setName( const std::tstring& name ) {
	this->name = name;
}
const std::tstring& Object::getName() const {
	return this->name;
}