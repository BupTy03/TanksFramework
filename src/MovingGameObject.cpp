#include "MovingGameObject.hpp"


namespace tf
{
	MovingGameObject::MovingGameObject(GameObjectType type)
		: GameObject{type}
		, dir_{Direction::forward()}
		, step_{0.f}
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

	void MovingGameObject::setDirection(const Direction& dir) 
	{ 
		dir_ = dir;
	}

	void MovingGameObject::outOfScreenEvent(const sf::RenderWindow& win)
	{
		setDirection(getDirection().inversed());
	}
}
