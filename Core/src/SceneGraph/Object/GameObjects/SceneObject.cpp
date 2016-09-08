#include "SceneGraph/Object/GameObjects/SceneObject.h"
#include "SceneGraph/Component/Component.h"

SceneObject::SceneObject( const std::tstring& name )
	:GameObject( name ) {}
SceneObject::~SceneObject() {}

bool SceneObject::Initialize() {
	return GameObject::Initialize();
}
void SceneObject::Update() {
	return GameObject::Update();
}
void SceneObject::Draw() {
	for( Component* obj : GetComponents() ) {
		IDrawable* drawable_obj = dynamic_cast< IDrawable* >( obj );
		if( drawable_obj == nullptr )
			continue;

		if( drawable_obj->GetCanDraw() )
			drawable_obj->Draw();
	}
	for( GameObject* obj : GetChilderen() ) {
		IDrawable* drawable_obj = dynamic_cast< IDrawable* >( obj );
		if( drawable_obj == nullptr )
			continue;

		if( drawable_obj->GetCanDraw() )
			drawable_obj->Draw();
	}
}
bool SceneObject::Shutdown() {
	return GameObject::Shutdown();
}