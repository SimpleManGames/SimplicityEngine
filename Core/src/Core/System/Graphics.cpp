#include "Core/System/Graphics.h"
#include "Core/System/MainWindow.h"
#include "Core/System/Manager/SystemManager.h"

#include "Diagnostics/Logger.h"

#include "Defines/Types/SystemType.h"
#include "Defines/deletemacros.h"

#include "Helpers/Singleton.h"

Graphics::Graphics()
	: System( SystemType::GRAPHICS_SYSTEM )

	, mainWindow( nullptr ) {}
Graphics::~Graphics() {}

bool Graphics::Initialize() {
	this->mainWindow = dynamic_cast< MainWindow* >( Singleton<SystemManager>::GetInstance().getSystem( SystemType::WINDOW_SYSTEM ) );

	return true;
}
void Graphics::Update() {}
void Graphics::Draw() {}
bool Graphics::Shutdown() {
	return true;
}