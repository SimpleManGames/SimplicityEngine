#ifndef _MYSCENE_H
#define _MYSCENE_H

#include "SceneGraph/Scene/Scene.h"
#include "Core\System\Input.h"
#include "Defines\vertex.h"
#include "Defines\geometry.h"

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
	Camera * camera;
	Input * input;

	SceneObject * cubeObject;

	Geometry cube;

	const char * vertS = "#version 150\n" "in vec4 position;" "void main() { gl_Position = position; }";
	const char * fragS = "#version 150\n" "out vec4 outColor;" "void main() { outColor = gl_Position; }";
};

#endif