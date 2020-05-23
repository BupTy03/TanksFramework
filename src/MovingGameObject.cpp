#include "MovingGameObject.hpp"


namespace tf
{
	MovingGameObject::MovingGameObject(GameObjectType type)
		: GameObject{type}
		, dir_{Direction::FORWARD}
		, step_{0} 
	{}

	float MovingGameObject::getStep() const
	{ 
		return step_; 
	}

	void MovingGameObject::setStep(float step) 
	{ 
		step_ = step; 
	}

	Direction MovingGameObject::getDirection() const 
	{ 
		return dir_;
	}

	void MovingGameObject::setDirection(Direction dir) 
	{ 
		dir_ = dir;
	}

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
		default:
			break;
		}
	}
}
