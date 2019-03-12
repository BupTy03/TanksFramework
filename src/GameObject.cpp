#include "GameObject.hpp"

namespace tf
{

	GameObject::GameObject() 
		: id_{counter_++}
	{
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

	std::size_t GameObject::counter_ = 1;

}