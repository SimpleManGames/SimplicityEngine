#ifndef _MAINTIMER_H
#define _MAINTIMER_H

#include "Core/System/System.h"

#ifndef _STRING_H
#include "Defines/string.h"
#endif

#ifndef _VECTOR_
#include <vector>
#endif

class Timer;

class MainTimer : public System {
public:
	MainTimer();
	virtual ~MainTimer();

	virtual bool Initialize();
	virtual void Update();
	virtual bool Shutdown();

	Timer* GetWorldTimer() const;

	void AddTimer( Timer* timer );
	Timer* GetTimer( const std::tstring& name ) const;

	static float deltaTime;

private:
	Timer* worldTimer;
	std::vector<Timer*> timers;
};

#endif //_GAMETIMER_H