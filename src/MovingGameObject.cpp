#include "MovingGameObject.hpp"

#include <chrono>
#include <iostream>

namespace tf
{
	MovingGameObject::MovingGameObject(std::shared_ptr<sf::RenderWindow> w, GameObjectType type, float step)
		: GameObject{std::move(w), type}
		, step_{step}
	{
	}

	void MovingGameObject::outOfScreenEvent()
	{
		switch (dir_)
		{
		case Direction::FORWARD:
			setDirection(Direction::BACKWARD);
			break;
		case Direction::BACKWARD:
			setDirection(Direction::FORWARD);
			break;
		case Direction::LEFT:
			setDirection(Direction::RIGHT);
			break;
		case Direction::RIGHT:
			setDirection(Direction::LEFT);
			break;
		}
	}
}