#include "SceneGraph/Scene/MyScene.h"

MyScene::MyScene()
	: Scene( _T( "MyScene" ) ) {}
MyScene::~MyScene() {}

bool MyScene::Initialize() {
	return Scene::Initialize();
}
void MyScene::Update() {
	Scene::Update();
}
bool MyScene::Shutdown() {
	return Scene::Shutdown();
}