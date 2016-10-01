#include "Core/Rendering/Renderer.h"

#include "Core/System/Graphics.h"
#include "Core/System/Manager/SystemManager.h"

#include "GLEW\glew.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

#include "Diagnostics/Logger.h"

#include "Defines\assert.h"
#include "Defines\deletemacros.h"
#include "Defines\systemdefines.h"

#include "Helpers/Singleton.h"

Renderer::Renderer() {}
Renderer::~Renderer() {}

bool Renderer::Initialize() {
	this->graphics = GetSystem( Graphics, SystemType::GRAPHICS_SYSTEM );
	assert( this->graphics != nullptr );

	return true;
}
bool Renderer::Shutdown() {
	return true;
}