#ifndef _MYSCENE_H
#define _MYSCENE_H

#include "SceneGraph/Scene/Scene.h"
#include "Core\System\Input.h"
#include "Defines\vertex.h"

class SceneObject;

class MyScene : public Scene {
public:
	MyScene();
	virtual ~MyScene();

	virtual bool Initialize();
	virtual void Update();
	virtual bool Shutdown();

private:
	Input * input;

	SceneObject* rectangle;
	SceneObject* circle;
	SceneObject* triangle;

	Vertex verts[ 3 ] = { { {    0,  .5f, 0, 1 } },
						  { {  .5f, -.5f, 0, 1 } },
						  { { -.5f, -.5f, 0, 1 } } }; 

	unsigned tris[ 3 ] = { 2, 1, 0 };

	const char * vertS = "#version 150\n" "in vec4 position;" "void main() { gl_Position = position; }";
	const char * fragS = "#version 150\n" "out vec4 outColor;" "void main() { outColor = vec4(1.0, 0.0, 0.0, 1.0); }";
};

#endif