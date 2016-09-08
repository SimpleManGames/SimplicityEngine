#include "Core/System/Manager/SystemManager.h"

#ifndef _ALGORITHM
#include <algorithm>
#endif

#include "Core/System/System.h"
#include "Core/System/Manager/SystemFactory.h"

#include "Interfaces/IDrawable.h"

#include "Defines/Types/SystemType.h"
#include "Defines/deletemacros.h"

#include "Helpers/Singleton.h"

SystemManager::SystemManager()
	:factory( nullptr ) {}
SystemManager::~SystemManager() {}

System* SystemManager::getSystem( SystemType type ) {
	std::vector<System*>::const_iterator it = std::find_if( this->systems.begin(), this->systems.end(),
															[ type ]( System* s ) -> bool {
		return s->GetType() == type;
	} );
	if( it != this->systems.end() )
		return ( *it );

	System* new_system = this->factory->createSystem( type );

	if( dynamic_cast< IDrawable* >( new_system ) != nullptr )
		this->drawableSystems.push_back( new_system );
	this->systems.push_back( new_system );

	return new_system;
}

std::vector<System*>& SystemManager::getDrawableSystems() { return this->drawableSystems; }
std::vector<System*>& SystemManager::getSystems() {	return this->systems; }

bool SystemManager::Initialize() {
	this->factory = new SystemFactory();

	return true;
}
bool SystemManager::Shutdown() {
	SafeDelete( this->factory );

	bool result = true;
	for( System* system : this->systems ) {
		if( !system->Shutdown() )
			result = false;

		SafeDelete( system );
	}

	this->systems.clear();
	this->drawableSystems.clear();

	return result;
}