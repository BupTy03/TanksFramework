#include "MovingGameObject.hpp"

namespace tf
{

	MovingGameObject::MovingGameObject()
		: GameObject()
		, timer_{new GameTimer()}
	{
	}

	MovingGameObject::~MovingGameObject()
	{
	}

	sf::Vector2f MovingGameObject::getIncrement()
	{
		return increment_;
	}

	void MovingGameObject::setIncrement(sf::Vector2f inc)
	{
		increment_ = inc;
	}

	std::size_t MovingGameObject::getStep()
	{
		return step_;
	}
	void MovingGameObject::setStep(std::size_t step)
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

	void MovingGameObject::handleEvent(Observable& observ)
	{
	}

}