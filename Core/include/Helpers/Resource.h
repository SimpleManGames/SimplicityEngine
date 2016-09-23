#ifndef _RESOURCE_H
#define _RESOURCE_H

template<typename T>
class Resource {
public:
	Resource<T>();
	~Resource<T>();

	T operator*();
private:
	T resource;
};
#endif // !_RESOURCE_H