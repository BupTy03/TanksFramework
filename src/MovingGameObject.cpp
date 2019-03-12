#include "MovingGameObject.hpp"

#include <random>

namespace tf
{

	MovingGameObject::MovingGameObject()
		: GameObject()
		, timer_{new GameTimer()}
	{
	}

	MovingGameObject::MovingGameObject(sf::Vector2f d)
		: GameObject()
		, timer_{new GameTimer()}
		, d_{d}
	{
	}

	MovingGameObject::~MovingGameObject()
	{
		delete timer_;
	}

	sf::Vector2f MovingGameObject::getDelta()
	{
		return d_;
	}

	void MovingGameObject::setDelta(sf::Vector2f d)
	{
		d_ = d;
	}

	void MovingGameObject::changeDirection(Direction dir)
	{
		switch (dir) {
			case Direction::LEFT:
				if(d_.x > 0.f) {
					d_.x *= -1.f;
				}
				break;
			case Direction::RIGHT:
				if(d_.x < 0.f) {
					d_.x *= -1.f;
				}
				break;
			case Direction::FORWARD:
				if(d_.y > 0.f) {
					d_.y *= -1.f;
				}
				break;
			case Direction::BACKWARD:
				if(d_.y < 0.f) {
					d_.y *= -1.f;
				}
				break;
			case Direction::FORWARD_LEFT:
				if(d_.x > 0.f) {
					d_.x *= -1.f;
				}	
				if(d_.y > 0.f) {
					d_.y *= -1.f;
				}
				break;
			case Direction::FORWARD_RIGHT:
				if(d_.x < 0.f) {
					d_.x *= -1.f;
				}	
				if(d_.y > 0.f) {
					d_.y *= -1.f;
				}
				break;
			case Direction::BACKWARD_LEFT:
				if(d_.x > 0.f) {
					d_.x *= -1.f;
				}	
				if(d_.y < 0.f) {
					d_.y *= -1.f;
				}
				break;
			case Direction::BACKWARD_RIGHT:
				if(d_.x < 0.f) {
					d_.x *= -1.f;
				}	
				if(d_.y < 0.f) {
					d_.y *= -1.f;
				}
				break;
			default:
				break;
		}
	}

	Direction MovingGameObject::getRandomDirection(Direction from, Direction to)
	{
		std::default_random_engine generator;
		std::uniform_int_distribution<int> distribution(static_cast<int>(from), static_cast<int>(to));
		return static_cast<Direction>(distribution(generator));
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

}