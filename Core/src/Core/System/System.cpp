#include "Core\System\System.h"

#include "Defines/Types/SystemType.h"

System::System( SystemType type )
	:systemType( type )
	, active( true ) {}
System::~System() {}

void System::Activate() {
	this->active = true;
}
void System::Deactivate() {
	this->active = false;
}

bool System::GetIsActive() const {
	return this->active;
}

SystemType System::GetType() const {
	return this->systemType;
}