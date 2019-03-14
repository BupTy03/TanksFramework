#include "GameObject.hpp"
#include "GameEventsManager.hpp"

namespace tf
{

	GameObject::GameObject() 
		: id_{counter_++}
	{
		(GameEventsManager::Instance()).addGameObject(this);
	}

	GameObject::~GameObject()
	{
	}

	std::size_t GameObject::getId()
	{
		return id_;
	}

	void GameObject::deleteLater()
	{
		deleted_ = true;
	}

	bool GameObject::isDeleted() const
	{
		return deleted_;
	}

	void GameObject::keyEvent(sf::Keyboard::Key which)
	{
	}

	void GameObject::outOfScreenEvent()
	{
	}

	std::size_t GameObject::counter_ = 1;

}