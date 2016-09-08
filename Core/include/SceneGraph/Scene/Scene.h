#ifndef _SCENE_H
#define _SCENE_H

#include "SceneGraph/Object.h"
#include "Interfaces\IDrawable.h"

#ifndef _VECTOR_
#include <vector>
#endif
#ifndef _STRING_H
#include "Defines\string.h"
#endif

class GameObject;
class Renderer;

class Scene : public Object, public IDrawable {
public:
	Scene( const std::tstring& name );
	virtual ~Scene();

	virtual bool Initialize();
	virtual void Update();
	virtual void Draw();
	virtual bool Shutdown();

	virtual void Activate();
	virtual void Deactive();

	virtual void Destroy();

	void AddGameObject( GameObject* object );
	void RemoveGameObject( GameObject* object );

	void SetRenderer( Renderer* renderer );
	Renderer* GetRenderer() const;

private:
	Renderer* renderer;
	std::vector<GameObject*> objects;
};

#endif //_SCENE_H

