#include "Core/System/Manager/SystemFactory.h"

#include "Defines\Types\SystemType.h"

#include "Core\System\System.h"
#include "Core\System\MainWindow.h"
#include "Core\System\Graphics.h"
#include "Core\System\Logic.h"
#include "Core\System\MainTimer.h"
#include "Core\System\Input.h"

SystemFactory::SystemFactory() {}
SystemFactory::~SystemFactory() {}

System* SystemFactory::createSystem( SystemType type ) {
	switch( type ) {
		case SystemType::WINDOW_SYSTEM: return new MainWindow();
		case SystemType::INPUT_SYSTEM: return new Input();
		case SystemType::LOGIC_SYSTEM: return new Logic();
		case SystemType::TIMER_SYSTEM: return new MainTimer();
		case SystemType::GRAPHICS_SYSTEM: return new Graphics();
	}

	return nullptr;
}