#include "Bullet.hpp"
#include "Wall.hpp"

#define DEBUG
#include <cassert>

namespace tf
{

	Bullet::Bullet(float step, float sz, sf::Vector2f pos)
		: MovingGameObject(GameObjectType::BULLET, step)
		, rectShape_{new sf::RectangleShape({sz, sz})}
		, moveTimer_{new GameTimer} 
	{
		rectShape_->setPosition(pos);
		rectShape_->setOutlineThickness(-sz / 9.f);
		rectShape_->setFillColor(sf::Color(220, 20, 60));
		rectShape_->setOutlineColor(sf::Color(144, 0, 32));
		moveTimer_->onTimerCall.connect(this, &Bullet::makeStep);
		moveTimer_->start(100);
	}

	Bullet::~Bullet()
	{
		delete rectShape_; 
		delete moveTimer_;
	}

	void Bullet::makeStep()
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
	}

	void Bullet::setSize(float sz)
	{
		rectShape_->setOutlineThickness(-sz / 9.f);
		rectShape_->setSize({sz, sz});
	}

}