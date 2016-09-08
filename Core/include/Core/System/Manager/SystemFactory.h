#ifndef _SYSTEMFACTORY_H
#define _SYSTEMFACTORY_H

#ifndef _SYSTEMTYPE_H
#include "Defines/Types/SystemType.h"
#endif

class System;

class SystemFactory {
public:
	SystemFactory();
	~SystemFactory();

	System* createSystem( SystemType type );
};

#endif // _SYSTEMFACTORY_H
