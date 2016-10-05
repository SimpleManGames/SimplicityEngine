#ifndef _SCENEOBJECT_H
#define _SCENEOBJECT_H

#include "SceneGraph\Object\GameObjects\GameObject.h"
#include "Interfaces\IDrawable.h"

#include "SceneGraph\Component\TransformComponent.h"

class SceneObject : public GameObject, public IDrawable {
public:
	SceneObject( const std::tstring& name = _T( "" ) );
	virtual ~SceneObject();

	virtual bool Initialize();
	virtual void Update();
	virtual void Draw();
	virtual bool Shutdown();
private:
	TransformComponent * transform;
};

#endif