#include "Core/System/MainTimer.h"

#include "SceneGraph/Object/Objects/Timer.h"

#include "Defines/Types/SystemType.h"
#include "Defines/deletemacros.h"

float MainTimer::deltaTime = 0.0f;

MainTimer::MainTimer()
	:System( SystemType::TIMER_SYSTEM ) {}
MainTimer::~MainTimer() {}

bool MainTimer::Initialize() {
	this->worldTimer = new Timer( _T( "WorldTimer" ) );

	if( !this->worldTimer->Initialize() )
		return false;
	this->worldTimer->SetInitialized();

	return true;
}
void MainTimer::Update() {
	this->worldTimer->Update();
	this->deltaTime = this->worldTimer->GetDeltaTime();

	for( Timer* t : this->timers )
		t->Update();
}
bool MainTimer::Shutdown() {
	SafeDelete( this->worldTimer );

	for( Timer* t : this->timers ) {
		if( !t->Shutdown() )
			return false;

		SafeDelete( t );
	}

	return true;
}

Timer* MainTimer::GetWorldTimer() const {
	return this->worldTimer;
}

void MainTimer::AddTimer( Timer* timer ) {

}
Timer* MainTimer::GetTimer( const std::tstring& name ) const {
	return nullptr;
}