#include "Tank.hpp"

#include <iostream>
#include <random>
#include <chrono>

namespace tf
{

	Tank::Tank()
		: MovingGameObject()
		, changeDirectionTimer_(new GameTimer())
		, body_{6}
		, randEngine_{static_cast<unsigned int>(
			((std::chrono::steady_clock::now()).time_since_epoch()).count()
		)}
	{
		for(std::size_t i = 0; i < body_.size(); ++i) {
			body_[i] = new sf::RectangleShape();
			body_[i]->setFillColor(sf::Color(220, 20, 60));
			body_[i]->setOutlineColor(sf::Color(144, 0, 32));
		}

		timer_->onTimerCall.connect(this, &Tank::makeStep);
		changeDirectionTimer_->onTimerCall.connect(this, &Tank::setRandDirection);

		timer_->start(1000);
		changeDirectionTimer_->start(4000);
	}
	Tank::Tank(sf::Vector2f pos, float sz)
		: MovingGameObject()
		, changeDirectionTimer_(new GameTimer())
		, body_{6}
		, randEngine_{static_cast<unsigned int>(
			((std::chrono::steady_clock::now()).time_since_epoch()).count()
		)}
	{
		for(std::size_t i = 0; i < body_.size(); ++i) {
			body_[i] = new sf::RectangleShape({sz, sz});
			body_[i]->setFillColor(sf::Color(220, 20, 60));
			body_[i]->setOutlineColor(sf::Color(144, 0, 32));
			body_[i]->setOutlineThickness(-sz / 9.f);
		}
		setPosition(pos);

		timer_->onTimerCall.connect(this, &Tank::makeStep);
		changeDirectionTimer_->onTimerCall.connect(this, &Tank::setRandDirection);

		timer_->start(1000);
		changeDirectionTimer_->start(4000);
	}
	Tank::Tank(sf::Vector2f pos, float sz, float step)
		: MovingGameObject(step)
		, changeDirectionTimer_(new GameTimer())
		, body_{6}
		, randEngine_{static_cast<unsigned int>(
			((std::chrono::steady_clock::now()).time_since_epoch()).count()
		)}
	{
		for(std::size_t i = 0; i < body_.size(); ++i) {
			body_[i] = new sf::RectangleShape({sz, sz});
			body_[i]->setFillColor(sf::Color(220, 20, 60));
			body_[i]->setOutlineColor(sf::Color(144, 0, 32));
			body_[i]->setOutlineThickness(-sz / 9.f);
		}
		setPosition(pos);

		timer_->onTimerCall.connect(this, &Tank::makeStep);
		changeDirectionTimer_->onTimerCall.connect(this, &Tank::setRandDirection);

		timer_->start(1000);
		changeDirectionTimer_->start(4000);
	}

	Tank::~Tank()
	{
		for(auto sh : body_) {
			delete sh;
		}

		for(auto b : bullets_) {
			delete b;
		}

		delete changeDirectionTimer_;
	}

	void Tank::draw(sf::RenderWindow& w)
	{
		for(auto sh : body_) {
			w.draw(*sh);
		}
	}

	float Tank::getSize() const
	{
		return body_[0]->getSize().x;
	}
	void Tank::setSize(float sz)
	{
		for(auto sh : body_) {
			sh->setSize({sz, sz});
			sh->setOutlineThickness(-sz / 9.f);
		}
		turn(getDirection());
	}

	sf::Vector2f Tank::getPosition() const
	{
		return currPos_;
	}
	void Tank::setPosition(sf::Vector2f pos)
	{
		currPos_ = pos;
	}

	void Tank::turn(Direction dir)
	{
		const auto sz = getSize();
		switch (dir) {
		case Direction::FORWARD:
			body_[0]->setPosition({currPos_.x + sz, currPos_.y});
			body_[1]->setPosition({currPos_.x, currPos_.y + sz});
			body_[2]->setPosition({currPos_.x + sz, currPos_.y + sz});
			body_[3]->setPosition({currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[4]->setPosition({currPos_.x, currPos_.y + 2.f * sz});
			body_[5]->setPosition({currPos_.x + 2.f * sz, currPos_.y + 2.f * sz});
			break;
		case Direction::BACKWARD:
			body_[0]->setPosition({currPos_.x, currPos_.y});
			body_[1]->setPosition({currPos_.x + 2.f * sz, currPos_.y});
			body_[2]->setPosition({currPos_.x, currPos_.y + sz});
			body_[3]->setPosition({currPos_.x + sz, currPos_.y + sz});
			body_[4]->setPosition({currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[5]->setPosition({currPos_.x + sz, currPos_.y + 2.f * sz});
			break;
		case Direction::LEFT:
			body_[0]->setPosition({currPos_.x + sz, currPos_.y});
			body_[1]->setPosition({currPos_.x + 2.f * sz, currPos_.y});
			body_[2]->setPosition({currPos_.x, currPos_.y + sz});
			body_[3]->setPosition({currPos_.x + sz, currPos_.y + sz});
			body_[4]->setPosition({currPos_.x + sz, currPos_.y + 2.f * sz});
			body_[5]->setPosition({currPos_.x + 2.f * sz, currPos_.y + 2.f * sz});
			break;
		case Direction::RIGHT:
			body_[0]->setPosition({currPos_.x, currPos_.y});
			body_[1]->setPosition({currPos_.x + sz, currPos_.y});
			body_[2]->setPosition({currPos_.x + sz, currPos_.y + sz});
			body_[3]->setPosition({currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[4]->setPosition({currPos_.x, currPos_.y + 2.f * sz});
			body_[5]->setPosition({currPos_.x + sz, currPos_.y + 2.f * sz});
			break;
		}
	}

	void Tank::setDirection(Direction dir)
	{
		MovingGameObject::setDirection(dir);
		turn(dir);
	}

	void Tank::makeShot()
	{
	}
	void Tank::makeStep()
	{
		const auto ps = getPosition();
		const auto step = getStep();
		switch (getDirection())
		{
			case Direction::FORWARD:
				setPosition({ps.x, ps.y - step});
				break;
			case Direction::BACKWARD:
				setPosition({ps.x, ps.y + step});
				break;
			case Direction::LEFT:
				setPosition({ps.x - step, ps.y});
				break;
			case Direction::RIGHT:
				setPosition({ps.x + step, ps.y});
				break;
		}
		turn(getDirection());
	}

	void Tank::setRandDirection()
	{
		std::uniform_int_distribution<int> distribution(0, 3);
		setDirection(static_cast<Direction>(distribution(randEngine_)));
	}

	const std::vector<Bullet*>& Tank::getBullets()
	{
		return bullets_;
	}

	void Tank::outOfScreenEvent()
	{
		MovingGameObject::outOfScreenEvent();
		turn(getDirection());
	}

}