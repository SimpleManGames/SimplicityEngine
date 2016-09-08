#include "SceneGraph/Component/Component.h"

#include "SceneGraph/Object/GameObjects/GameObject.h"

Component::Component( const std::tstring& name )
	:Object( name )
	, parent( nullptr )
	, order_id( INVALID_ORDER_ID ) {}
Component::~Component() {}

int Component::GetOrderValue() const {
	return this->order_id;
}
void Component::SetOrderValue( int value ) {
	this->order_id = value;
}

void Component::SetParent( GameObject* parent ) {
	this->parent = parent;
}
GameObject* Component::GetParent() const {
	return this->parent;
}