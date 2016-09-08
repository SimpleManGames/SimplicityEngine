#ifndef _SYSTEM_H
#define _SYSTEM_H

#ifndef _SYSTEMTYPE_H
	#include "Defines/Types/SystemType.h"
#endif

class System 
{
public:
	System(SystemType type);
	virtual ~System();

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual bool Shutdown() = 0;

	void Activate();
	void Deactivate();

	bool GetIsActive() const;

	SystemType GetType() const;

private:
	SystemType systemType;
	bool active;
};

#endif // _SYSTEM_H

