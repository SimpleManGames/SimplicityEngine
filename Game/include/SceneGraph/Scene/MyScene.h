#ifndef _MYSCENE_H
#define _MYSCENE_H
#include "SceneGraph/Scene/Scene.h"
#include "SceneGraph/Object/GameObjects/SceneObject.h"
#include "SceneGraph\Component\RenderComponent.h"

#include "Core\System\Input.h"
#include "Core\System\MainTimer.h"

#include "Defines\geometry.h"
#include "Defines\systemdefines.h"

#include "Helpers\Singleton.h"
#include "Core\System\Manager\ResourceManager.h"

#include "Camera.h"

class SceneObject;

class MyScene : public Scene {
public:
	MyScene();
	virtual ~MyScene();

	virtual bool Initialize();
	virtual void Update();
	virtual bool Shutdown();

private:
};

#endif