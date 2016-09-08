#include "SceneGraph/Scene/Scene.h"
#include "SceneGraph/Object/GameObjects/GameObject.h"

#ifndef _ALGORITHM
#include <algorithm>
#endif

#include "Defines\deletemacros.h"

#include "Helpers/Singleton.h"

#include "Interfaces/IDrawable.h"

Scene::Scene( const std::tstring& name )
	:Object( name )
	, renderer( nullptr ) {}
Scene::~Scene() {}

bool Scene::Initialize() {
	for( GameObject* obj : this->objects ) {
		if( obj->GetInitialized() )
			continue;
		if( !obj->Initialize() )
			return false;
	}

	return true;
}
void Scene::Update() {
	for( GameObject* obj : this->objects ) {
		if( obj->isActive() )
			obj->Update();
	}
}
void Scene::Draw() {
	for( GameObject* obj : this->objects ) {
		IDrawable* drawable_obj = dynamic_cast< IDrawable* >( obj );
		if( drawable_obj == nullptr )
			continue;

		if( drawable_obj->GetCanDraw() )
			drawable_obj->Draw();
	}
}
bool Scene::Shutdown() {
	for( GameObject* obj : this->objects ) {
		if( !obj->Shutdown() )
			return false;
		SafeDelete( obj );
	}
	this->objects.clear();

	return true;
}

void Scene::Activate() {
	Object::Activate();
}
void Scene::Deactive() {
	Object::Deactive();
}

void Scene::Destroy() {
	Object::Destroy();
}

void Scene::AddGameObject( GameObject* object ) {
	std::vector<GameObject*>::iterator it = std::find( this->objects.begin(), this->objects.end(), object );
	if( it == this->objects.end() ) {
		this->objects.push_back( object );
		object->SetScene( this );
	}
}
void Scene::RemoveGameObject( GameObject* object ) {
	std::vector<GameObject*>::iterator it = std::find( this->objects.begin(), this->objects.end(), object );
	if( it != this->objects.end() ) {
		this->objects.erase( it );
		SafeDelete( ( *it ) );
	}
}

void Scene::SetRenderer( Renderer* renderer ) {
	this->renderer = renderer;
}
Renderer* Scene::GetRenderer() const {
	return this->renderer;
}