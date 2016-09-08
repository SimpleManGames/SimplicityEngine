#ifndef _TIMER_H
#define _TIMER_H

#include "SceneGraph\Object.h"

class Timer : public Object {
public:

	Timer( const std::tstring& name );
	virtual ~Timer();

	virtual bool Initialize();
	void Update();
	virtual bool Shutdown();

	float GetTotalTime() const;		//in seconds
	float GetDeltaTime() const;		//in seconds

	void Reset();
private:

	void Start();
	void Stop();

	double secondspercount;
	double deltaTime;

	_int64 baseTime;
	_int64 pauseTime;
	_int64 stopTime;
	_int64 prevTime;
	_int64 currTime;

	bool stopped;
};

#endif //_GAMETIMER_H