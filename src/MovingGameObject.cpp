#include "MovingGameObject.hpp"

#include <chrono>
#include <iostream>

namespace tf
{

	MovingGameObject::MovingGameObject(std::shared_ptr<sf::RenderWindow> w)
		: GameObject(std::move(w))
	{
	}

	MovingGameObject::MovingGameObject(std::shared_ptr<sf::RenderWindow> w, float step)
		: GameObject(std::move(w))
		, step_{step}
	{
	}

	MovingGameObject::~MovingGameObject()
	{
	}

	float MovingGameObject::getStep()
	{
		return step_;
	}
	void MovingGameObject::setStep(float step)
	{
		step_ = step;
	}

	Direction MovingGameObject::getDirection()
	{
		return dir_;
	}
	void MovingGameObject::setDirection(Direction dir)
	{
		dir_ = dir;
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