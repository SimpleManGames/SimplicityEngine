#ifndef _SINGLETON_H
#define _SINGLETON_H

#ifndef _ASSERT_H
#include "assert.h"
#endif
#ifndef _DELETEMACROS_H
#include "Defines/deletemacros.h"
#endif

template <typename T>
class Singleton {
public:
	static bool CreateInstance() {
		if( Singleton::instance != nullptr )
			return false;

		Singleton::instance = new T;
		return true;
	}
	static void DestroyInstance() {
		SafeDelete( Singleton::instance );
	}

	static T& GetInstance() {
		assert( Singleton::instance != nullptr );
		return *( Singleton::instance );
	}

	static bool HasInstance() {
		return instance != nullptr;
	}

protected:
	Singleton() {}
	virtual ~Singleton() {}

private:

	//Disable copy constructor & assignment operator
	Singleton( Singleton const& ) {}
	Singleton& operator=( Singleton const& ) {}

	static T* instance;
};

template<typename T>
T * Singleton<T>::instance = nullptr;

#endif // _SINGLETON_H