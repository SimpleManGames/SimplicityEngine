#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "SceneGraph\Object.h"

#ifndef _STRING_H
#include "Defines\string.h"
#endif

class GameObject;

class Component : public Object {
public:
	Component( const std::tstring& name = _T( "" ) );
	virtual ~Component();

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual bool Shutdown() = 0;

	void SetOrderValue( int value );
	int GetOrderValue() const;

	void SetParent( GameObject* parent );
	GameObject* GetParent() const;

	static const int INVALID_ORDER_ID = -1;

private:
	GameObject* parent;

	int order_id;
};

#endif

