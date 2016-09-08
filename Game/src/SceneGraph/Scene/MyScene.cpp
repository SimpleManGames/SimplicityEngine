#include "SceneGraph/Scene/MyScene.h"

#include "SceneGraph/Object/GameObjects/SceneObject.h"
#include "SceneGraph/Object/Objects/Shapes/RectShape.h"
#include "SceneGraph/Object/Objects/Shapes/CircleShape.h"
#include "SceneGraph/Component/ShapeComponent.h"

MyScene::MyScene()
	:Scene( _T( "MyScene" ) )
	, rectangle( nullptr )
	, circle( nullptr ) {}
MyScene::~MyScene() {}

bool MyScene::Initialize() {
	this->rectangle = new SceneObject();
	RectShape* rect_shape = new RectShape( 10, 10, 100, 100 );
	rect_shape->SetColor( Color( 1, 0, 0 ) );
	this->rectangle->AddComponent( new ShapeComponent( rect_shape ) ); // Ownership of the " RectShape " is transferred to the " ShapeComponent ".
	AddGameObject( this->rectangle );
	this->circle = new SceneObject();
	CircleShape* circle_shape = new CircleShape( 500, 500, 100 );
	circle_shape->SetColor( Color( 0, 0, 1 ) );
	this->circle->AddComponent( new ShapeComponent( circle_shape ) ); // Ownership of the " CircleShape " is transferred to the " ShapeComponent ".
	AddGameObject( this->circle );

	return Scene::Initialize();
}
void MyScene::update() {
	Scene::Update();
}
bool MyScene::Shutdown() {
	return Scene::Shutdown();
}