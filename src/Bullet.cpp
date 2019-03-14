#include "Bullet.hpp"

namespace tf
{

	void Bullet::init()
	{
		rectShape_.setFillColor(sf::Color(220, 20, 60));
		rectShape_.setOutlineColor(sf::Color(144, 0, 32));
		timer_->onTimerCall.connect(this, 
									&Bullet::makeStep);
		timer_->start(1000);
	}

	Bullet::Bullet()
		: MovingGameObject()
	{
		init();
	}
	Bullet::Bullet(sf::Vector2f pos, float sz) 
		: MovingGameObject()
		, rectShape_{{sz, sz}}
	{
		rectShape_.setPosition(pos);
		rectShape_.setOutlineThickness(-sz / 9.f);
		init();
	}
	Bullet::Bullet(sf::Vector2f pos, float sz, float step)
		: MovingGameObject(step)
		, rectShape_{{sz, sz}}
	{
		rectShape_.setPosition(pos);
		rectShape_.setOutlineThickness(-sz / 9.f);
		init();
	}
	Bullet::~Bullet()
	{
	}

	void Bullet::draw(sf::RenderWindow& w)
	{
		w.draw(rectShape_);
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

	float Bullet::getSize() const
	{
		return rectShape_.getSize().x;
	}
	void Bullet::setSize(float sz)
	{
		rectShape_.setOutlineThickness(-sz / 9.f);
		rectShape_.setSize({sz, sz});
	}

	sf::Vector2f Bullet::getPosition() const
	{
		return rectShape_.getPosition();
	}
	void Bullet::setPosition(sf::Vector2f pos)
	{
		rectShape_.setPosition(pos);
	}

	void Bullet::outOfScreenEvent()
	{
		deleteLater();
	}

}