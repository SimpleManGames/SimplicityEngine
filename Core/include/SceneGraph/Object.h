#ifndef _OBJECT_H
#define _OBJECT_H

#include "Helpers/ObjectCounter.h"

#ifndef _STRING_H
#include "Defines/string.h"
#endif

class Object : public ObjectCounter<Object> {
public:
	Object( const std::tstring& name = _T( "" ) );
	virtual ~Object();

	virtual bool Initialize() = 0;
	virtual bool Shutdown() = 0;

	void SetInitialized();
	bool GetInitialized();

	virtual void Activate();
	virtual void Deactive();
	bool isActive();

	virtual void Destroy();
	bool isDestroyed() const;

	void setName( const std::tstring& name );
	const std::tstring& getName() const;

protected:
	template<typename T>
	const std::tstring generateName( const std::tstring& partialName ) {
		return partialName + TOSTRING( ObjectCounter<T>::GetAmount() );
	}

private:
	bool active;

	bool initialized;
	bool destroyed;

	std::tstring name;
};

#endif //_OBJECT_H

