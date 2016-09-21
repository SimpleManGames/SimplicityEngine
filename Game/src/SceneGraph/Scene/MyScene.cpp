#include "SceneGraph/Scene/MyScene.h"

#include "SceneGraph/Object/GameObjects/SceneObject.h"
#include "SceneGraph/Object/Objects/Shapes/RectShape.h"
#include "SceneGraph/Object/Objects/Shapes/CircleShape.h"
#include "SceneGraph\Component\RenderComponent.h"
#include "SceneGraph/Component/ShapeComponent.h"

#include "Core\Rendering\crenderutils.h"

#include "Core\System\Manager\SystemManager.h"
#include "Core\System\MainTimer.h"

#include "Camera.h"

MyScene::MyScene()
	:Scene( _T( "MyScene" ) ) {}
MyScene::~MyScene() {}

bool MyScene::Initialize() {
	cube = LoadGeometry( "../res/model/cube.obj" );

	camera = new Camera();
	camera->JumpTo( glm::vec3( -5, -5, -5 ) );
	camera->LookAt( glm::vec3( 0, 0, 0 ) );

	input = dynamic_cast< Input* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::INPUT_SYSTEM ) );
	cubeObject = new SceneObject( _T( "Triangle" ) );
	this->cubeObject->AddComponent( new RenderComponent( cube, MakeShader( vertS, fragS ) ) );
	AddGameObject( this->cubeObject );

	return Scene::Initialize();
}
void MyScene::Update() {
	camera->Update( dynamic_cast< Input* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::INPUT_SYSTEM ) ), dynamic_cast< MainTimer* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::TIMER_SYSTEM ) ) );

	Scene::Update();
}
bool MyScene::Shutdown() {
	SafeDelete( camera );
	SafeDelete( cubeObject );
	return Scene::Shutdown();
}