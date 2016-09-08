#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include "Helpers/Manager.h"
#include "Interfaces\IDrawable.h"

#ifndef _VECTOR_
#include <vector>
#endif

#ifndef _STRING_H
#include "Defines/string.h"
#endif

#include "Core/Rendering/Renderer.h"

#include "Diagnostics/Logger.h"

class Scene;

class SceneManager : public Manager, public IDrawable {
public:
	SceneManager();
	virtual ~SceneManager();

	virtual bool Initialize();
	void Update();
	virtual void Draw();
	virtual bool Shutdown();

	void AddScene( Scene* scene );

	void SetActiveScene( const std::tstring& name );
	Scene* GetActiveScene() const;

private:
	template<typename T>
	void setupManager() {
		if( Singleton<T>::HasInstance() ) {
			Singleton<Logger>::GetInstance().Log( _T( "Check if we can keep data that will be used in a different scene aswell, so not all data need to be unloaded." ), LOGTYPE_TODO );
			Singleton<T>::GetInstance().Shutdown();
		} else Singleton<T>::CreateInstance();

		Singleton<T>::GetInstance().Initialize();
	}
	template<typename T>
	void destroyManager() {
		Singleton<T>::GetInstance().Shutdown();
		Singleton<T>::DestroyInstance();
	}

	Scene* activeScene;
	std::vector<Scene*> scenes;
};

#endif // _SCENEMANAGER_H