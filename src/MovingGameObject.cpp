#include "MovingGameObject.hpp"

#include <chrono>
#include <iostream>


namespace tf
{
	MovingGameObject::MovingGameObject(GameObjectType type, float step)
		: GameObject{type}
		, step_{step} {}

	void MovingGameObject::outOfScreenEvent(const sf::RenderWindow& win)
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