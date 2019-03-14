#include "MovingGameObject.hpp"

#include <chrono>
#include <iostream>

namespace tf
{

	MovingGameObject::MovingGameObject()
		: GameObject()
		, timer_{new GameTimer()}
	{
	}

	MovingGameObject::MovingGameObject(float step)
		: GameObject()
		, timer_{new GameTimer()}
		, step_{step}
	{
	}

	MovingGameObject::~MovingGameObject()
	{
		delete timer_;
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

	void MovingGameObject::startTimer()
	{
		timer_->start();
	}
	void MovingGameObject::startTimer(std::size_t msec)
	{
		timer_->start(msec);
	}
	void MovingGameObject::startTimer(std::chrono::milliseconds msec)
	{
		timer_->start(msec);
	}
	void MovingGameObject::stopTimer()
	{
		timer_->stop();
	}

	void MovingGameObject::setTimerInterval(std::size_t msec)
	{
		timer_->setInterval(msec);
	}
	void MovingGameObject::setTimerInterval(std::chrono::milliseconds msec)
	{
		timer_->setInterval(msec);
	}

	void MovingGameObject::setTimerSingleShot(bool sshot)
	{
		timer_->setSingleShot(sshot);
	}
	bool MovingGameObject::isTimerSingleShot()
	{
		return timer_->isSingleShot();
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