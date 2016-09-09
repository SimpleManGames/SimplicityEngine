#include "SceneGraph/Scene/MyScene.h"

#include "SceneGraph/Object/GameObjects/SceneObject.h"
#include "SceneGraph/Object/Objects/Shapes/RectShape.h"
#include "SceneGraph/Object/Objects/Shapes/CircleShape.h"
#include "SceneGraph\Component\RenderComponent.h"
#include "SceneGraph/Component/ShapeComponent.h"

#include "Core\Rendering\crenderutils.h"

#include "Core\System\Manager\SystemManager.h"

MyScene::MyScene()
	:Scene( _T( "MyScene" ) )
	, rectangle( nullptr )
	, circle( nullptr ) {}
MyScene::~MyScene() {}

bool MyScene::Initialize() {
	input = dynamic_cast< Input* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::INPUT_SYSTEM ) );
	triangle = new SceneObject();
	this->triangle->AddComponent( new RenderComponent( MakeGeometry( verts, 3, tris, 3 ), MakeShader( vertS, fragS ) ) );
	AddGameObject( this->triangle );

	return Scene::Initialize();
}
void MyScene::Update() {
	if( input->GetKeyState( 'A' ) == KeyState::DOWN )
		Singleton<Logger>::GetInstance().Log( _T( "Input Update" ), LOGTYPE_INFO );

	Scene::Update();
}
bool MyScene::Shutdown() {
	return Scene::Shutdown();
}