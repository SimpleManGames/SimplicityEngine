#include "SceneGraph/Scene/Manager/SceneManager.h"
#include "SceneGraph/Scene/Scene.h"

#ifndef _ALGORITHM_
#include <algorithm>
#endif

#include "Defines/assert.h"
#include "Defines/deletemacros.h"

#include "Helpers\Singleton.h"

namespace {
	class SceneWithName {
	public:
		SceneWithName( const std::tstring& name )
			:name( name ) {}

		bool operator()( Scene* scene ) {
			return scene->getName() == this->name;
		}

	private:
		std::tstring name;
	};
}

SceneManager::SceneManager()
	:activeScene( nullptr ) {}
SceneManager::~SceneManager() {}

bool SceneManager::Initialize() {
	setupManager<Renderer>();

	if( !this->activeScene->GetInitialized() ) {
		this->activeScene->SetRenderer( &Singleton<Renderer>::GetInstance() );

		if( !this->activeScene->Initialize() )
			return false;
		this->activeScene->SetInitialized();
	}
	return true;
}
void SceneManager::Update() {
	//Initialize the scene before trying to update it.
	assert( this->activeScene->GetInitialized() );

	if( this->activeScene->isActive() )
		this->activeScene->Update();
}
void SceneManager::Draw() {
	//Initialize the scene before trying to draw it.
	assert( this->activeScene->GetInitialized() );

	if( this->activeScene->GetCanDraw() && this->activeScene->isActive() )
		this->activeScene->Draw();
}
bool SceneManager::Shutdown() {
	for( Scene* scene : this->scenes ) {
		if( !scene->GetInitialized() ) {
			SafeDelete( scene );
			continue;
		}

		if( !scene->Shutdown() )
			return false;

		SafeDelete( scene );
	}

	destroyManager<Renderer>();

	return true;
}

void SceneManager::AddScene( Scene* scene ) {
	std::vector<Scene*>::iterator it = std::find( scenes.begin(), scenes.end(), scene );
	if( it == scenes.end() )
		scenes.push_back( scene );
}

void SceneManager::SetActiveScene( const std::tstring& name ) {
	std::vector<Scene*>::iterator it = std::find_if( scenes.begin(), scenes.end(), SceneWithName( name ) );

	//Scene with given name was not found.
	assert( it != scenes.end() );

	if( this->activeScene ) {
		this->activeScene->Deactive();
		this->activeScene->Destroy();
	}

	this->activeScene = ( *it );
	this->activeScene->Activate();

}
Scene* SceneManager::GetActiveScene() const {
	return this->activeScene;
}