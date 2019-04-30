#include "GameObject.hpp"
#include "GameEventsManager.hpp"

namespace tf
{

	GameObject::GameObject(std::shared_ptr<sf::RenderWindow> w, GameObjectType type) 
		: win_{std::move(w)}
		, id_{counter_++}
		, type_{type}
	{ (GameEventsManager::Instance()).addGameObject(this); }

	GameObject::~GameObject() { onDelete(this); }

	std::size_t GameObject::counter_ = 1;

}