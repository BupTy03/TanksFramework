#include "GameObject.hpp"
#include "GameEventsManager.hpp"

#include <cassert>


namespace tf
{
	GameObject::GameObject(GameObjectType type) 
		: id_{counter_++}
		, type_{type}
		, manager_{nullptr}
		, deleted_{false}
	{ }

	std::size_t GameObject::getId() const
	{ 
		return id_; 
	}

	GameObject::GameObjectType GameObject::getType() const 
	{ 
		return type_;
	}

	void GameObject::setGameEventsManager(GameEventsManager* manager)
	{
		assert(manager != nullptr);
		manager_ = manager;
	}

	void GameObject::deleteLater() 
	{ 
		deleted_ = true; 
	}

	bool GameObject::isDeleted() const
	{ 
		return deleted_; 
	}

	GameEventsManager* GameObject::getGameEventsManager() const
	{ 
		return manager_; 
	}

	GameObject::~GameObject() { onDelete(this); }

	std::size_t GameObject::counter_ = 1;

}
