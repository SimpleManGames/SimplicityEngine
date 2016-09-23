#include "SceneGraph/Scene/MyScene.h"

MyScene::MyScene()
	: Scene( _T( "MyScene" ) ) {}
MyScene::~MyScene() {}

bool MyScene::Initialize() {
	camera = new Camera();
	camera->JumpTo( glm::vec3( -5, -5, -5 ) );
	camera->LookAt( glm::vec3( 0, 0, 0 ) );
	view = camera->GetView();
	frame = Framebuffer_Internal::Make( 1280, 720, 1 );
	Framebuffer screen = { 0, 1280, 720, 1 };

	Singleton<ResourceManager>::GetInstance().Add<Geometry>( "Cube", "../res/models/cube.obj" );
	cubeObject = new SceneObject( _T( "Triangle" ) );
	Geometry cube = Singleton<ResourceManager>::GetInstance().Get<Geometry>( "Cube" );
	this->cubeObject->AddComponent( new RenderComponent( cube, Shader_Internal::Make( vertS, fragS ), screen ) );
	AddGameObject( this->cubeObject );

	return Scene::Initialize();
}
void MyScene::Update() {
	view = camera->GetView();
	proj = camera->GetProj();

	camera->Update( GetSystem(Input, SystemType::INPUT_SYSTEM), 
					GetSystem(MainTimer, SystemType::TIMER_SYSTEM ) );
	Scene::Update();
}
bool MyScene::Shutdown() {
	return Scene::Shutdown();
}