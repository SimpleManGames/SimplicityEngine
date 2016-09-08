#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "SceneGraph\Object.h"

#ifndef _SINGLETON_H
#include "Helpers/Singleton.h"
#endif
#ifndef _LOGGER_H
#include "Diagnostics/Logger.h"
#endif

#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _LIMITS_
#include <limits>
#endif

class Component;
class Scene;

class GameObject : public Object {
public:
	GameObject( const std::tstring& name = _T( "" ) );
	virtual ~GameObject();

	virtual bool Initialize();
	virtual void Update();
	virtual bool Shutdown();

	void SetScene( Scene* scene );
	Scene* GetScene() const;
	void SetParent( GameObject* parent );
	GameObject* GetParent() const;

	std::vector<GameObject*> GetChilderen() const;

	template <typename T> T* GetComponent() const;
	std::vector<Component*> GetComponents() const;

	void AddComponent( Component* component );
	void RemoveComponent( Component* component );

	void AddChild( GameObject* object );
	void RemoveChild( GameObject* object );

private:
	std::vector<GameObject*> childeren;
	std::vector<Component*> components;

	GameObject* parent;

	Scene* currentScene;
};

template <typename T>
T* GameObject::GetComponent() const {
	for( Component* c : this->components ) {
		T* newC = dynamic_cast< T* >( c );
		if( newC == nullptr )
			continue;

		return newC;
	}

	return nullptr;
}

#endif