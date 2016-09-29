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
	glm::mat4 proj, view, model;
	Camera * camera;

	SceneObject * cubeObject;
	
	Geometry cube;

	const char * vertS = "#version 150\n" "in vec4 position;" "void main() { gl_Position = position; }";
	const char * fragS = "#version 150\n" "out vec4 outColor;" "void main() { outColor = gl_Position; }";

	Framebuffer frame;
	Framebuffer screen = { 0, 1280, 720, 1 };
};

#endif