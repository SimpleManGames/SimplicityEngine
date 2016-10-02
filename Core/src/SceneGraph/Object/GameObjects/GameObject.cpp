#include "SceneGraph\Object\GameObjects\GameObject.h"

#include "SceneGraph\Component\Component.h"
#include "SceneGraph\Scene\Scene.h"

#ifndef _ALGORITHM_
#include <algorithm>
#endif

#include "Defines\deletemacros.h"

GameObject::GameObject( const std::tstring& name )
	:Object( name )
	, currentScene( nullptr )
	, parent( nullptr ) {}
GameObject::~GameObject() {}

bool GameObject::Initialize() {
	for( Component* obj : this->components ) {
		if( obj->GetInitialized() )
			continue;

		if( !obj->Initialize() )
			return false;
	}
	for( GameObject* child_obj : this->children ) {
		if( child_obj->Initialize() )
			continue;

		if( !child_obj->Initialize() )
			return false;
	}

	return true;
}
void GameObject::Update() {
	for( Component* obj : this->components ) {
		if( obj->isActive() )
			obj->Update();
	}
	for( GameObject* child_obj : this->children ) {
		if( child_obj->isActive() )
			child_obj->Update();
	}
}
bool GameObject::Shutdown() {
	for( Component* obj : this->components ) {
		if( !obj->Shutdown() )
			return false;
		SafeDelete( obj );
	}
	this->components.clear();
	for( GameObject* child_obj : this->children ) {
		if( !child_obj->Shutdown() )
			return false;
		SafeDelete( child_obj );
	}
	this->children.clear();
	return true;
}

void GameObject::SetScene( Scene* scene ) {
	this->currentScene = scene;
}
Scene* GameObject::GetScene() const {
	return this->currentScene;
}
void GameObject::SetParent( GameObject* parent ) {
	this->parent = parent;
}
GameObject* GameObject::GetParent() const {
	return this->parent;
}

std::vector<GameObject*> GameObject::GetChildren() const {
	return this->children;
}
std::vector<Component*> GameObject::GetAllComponents() const {
	return this->components;
}

void GameObject::AddComponent( Component* component ) {
	std::vector<Component*>::iterator it = std::find( this->components.begin(), this->components.end(), component );
	if( it == this->components.end() ) {
		this->components.push_back( component );
		component->SetParent( this );
		if( component->GetOrderValue() == Component::INVALID_ORDER_ID )
			component->SetOrderValue( this->components.size() );
	}
}
void GameObject::RemoveComponent( Component* component ) {
	std::vector<Component*>::iterator it = std::find( this->components.begin(), this->components.end(), component );
	if( it != this->components.end() ) {
		this->components.erase( it );
		SafeDelete( ( *it ) );
	}
}
void GameObject::AddChild( GameObject* child ) {
	std::vector<GameObject*>::iterator it = std::find( this->children.begin(), this->children.end(), child );
	if( it == this->children.end() ) {
		this->children.push_back( child );
		child->SetParent( this );
		child->SetScene( GetScene() );
	}
}
void GameObject::RemoveChild( GameObject* child ) {
	std::vector<GameObject*>::iterator it = std::find( this->children.begin(), this->children.end(), child );
	if( it != this->children.end() ) {
		this->children.erase( it );
		SafeDelete( ( *it ) );
	}
}