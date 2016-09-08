#ifndef _MANAGER_H
#define _MANAGER_H

class Manager {
public:
	Manager() {}
	virtual ~Manager() {}

	virtual bool Initialize() = 0;
	virtual bool Shutdown() = 0;
};

#endif //_MANAGER_H