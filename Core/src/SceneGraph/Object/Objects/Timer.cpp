#include "SceneGraph\Object\Objects\Timer.h"

//Additional Include Files
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _CTIME_
#include <ctime>
#endif

//Class GameTimer
Timer::Timer( const std::tstring& name )
	:Object( name )
	, secondspercount( 0.0 )
	, deltaTime( -1.0 )

	, baseTime( 0 )
	, pauseTime( 0 )
	, prevTime( 0 )
	, currTime( 0 )

	, stopped( false ) {
	_int64 countpersec;
	QueryPerformanceFrequency( ( LARGE_INTEGER* )&countpersec );
	this->secondspercount = 1.0 / ( double )countpersec;
}
Timer::~Timer() {}

float Timer::GetTotalTime()const {
	if( this->stopped )
		return ( float )( ( this->stopTime - this->baseTime )*this->secondspercount );

	else return ( float )( ( ( this->currTime - this->pauseTime ) - this->baseTime )*this->secondspercount );
}
float Timer::GetDeltaTime()const {
	return ( float )this->deltaTime;
}

void Timer::Reset() {
	_int64 currTime;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&currTime );

	this->baseTime = currTime;
	this->prevTime = currTime;
	this->stopTime = 0;

	this->stopped = false;
}

void Timer::Start() {
	_int64 startTime;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&startTime );
	this->prevTime = startTime;

	//if we are resuming tje timer from a stopped state ...
	if( this->stopped ) {
		//then accumulate the paused time.
		this->pauseTime += ( startTime - this->stopTime );

		//Since we are starting the timer back up,
		//the current previous time is not valid,
		//as it occurred while paused.
		//So reset it to the current time.
		this->prevTime = startTime;

		//no longer stopped ...
		this->stopTime = 0;
		this->stopped = false;
	}
}
void Timer::Stop() {
	//if we are already stopped, then don't do anything
	if( !this->stopped ) {
		_int64 currTime;
		QueryPerformanceCounter( ( LARGE_INTEGER* )&currTime );

		//Save the time we stopped at,
		//and set the boolean flag indiacting the timer stopped.
		this->stopTime = currTime;
		this->stopped = true;
	}
}

bool Timer::Initialize() {
	Start();
	return true;
}
void Timer::Update() {
	if( this->stopped ) {
		this->deltaTime = 0.0;
	}

	//get the time this frame
	_int64 currTime;
	QueryPerformanceCounter( ( LARGE_INTEGER* )&currTime );
	this->currTime = currTime;

	//Time diffrence between this frame and previous
	this->deltaTime = ( this->currTime - this->prevTime )*this->secondspercount;

	//Prepare for next frame
	this->prevTime = this->currTime;

	//Force nonnegative,
	//the DXSKS's CDXUTTimer metions that if the processor goes into power save mode or we get shuffled to another processor,
	//then this->delta_time can be negative.
	if( this->deltaTime < 0.0 )
		this->deltaTime = 0.0;
}
bool Timer::Shutdown() {
	Stop();
	return true;
}