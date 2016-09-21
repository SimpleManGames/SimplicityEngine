#include "SceneGraph/Scene/MyScene.h"

MyScene::MyScene()
	:Scene( _T( "MyScene" ) ) {}
MyScene::~MyScene() {}

bool MyScene::Initialize() {
	cube = LoadGeometry( "../res/models/cube.obj" );

	camera = new Camera();
	camera->JumpTo( glm::vec3( -5, -5, -5 ) );
	camera->LookAt( glm::vec3( 0, 0, 0 ) );

	input = GetSystem(Input, SystemType::INPUT_SYSTEM);
	cubeObject = new SceneObject( _T( "Triangle" ) );
	this->cubeObject->AddComponent( new RenderComponent( cube, MakeShader( vertS, fragS ) ) );
	AddGameObject( this->cubeObject );

	return Scene::Initialize();
}
void MyScene::Update() {
	camera->Update( input, GetSystem(MainTimer, SystemType::TIMER_SYSTEM ) ) );

	Scene::Update();
}
bool MyScene::Shutdown() {
	SafeDelete( camera );
	SafeDelete( cubeObject );
	return Scene::Shutdown();
}