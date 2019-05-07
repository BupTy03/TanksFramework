#include "GameObject.hpp"
#include "GameEventsManager.hpp"

#include <cassert>

namespace tf
{

	GameObject::GameObject(GameObjectType type) 
		: id_{counter_++}
		, type_{type}
	{ }

	void GameObject::setGameEventsManager(GameEventsManager* manager)
	{
		assert(manager != nullptr && "manager ptr was null!");
		manager_ = manager;
	}

	GameObject::~GameObject() { onDelete(this); }

	std::size_t GameObject::counter_ = 1;

}