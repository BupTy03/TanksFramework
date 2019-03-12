#include "Bullet.hpp"

namespace tf
{

	void Bullet::init()
	{
		rectShape_.setFillColor(sf::Color(220, 20, 60));
		rectShape_.setOutlineColor(sf::Color(144, 00, 32));
		timer_->start(1000);
		timer_->onTimerCall.connect(this, 
									&Bullet::makeStep);
	}

	Bullet::Bullet()
		: MovingGameObject()
	{
		init();
	}
	Bullet::Bullet(sf::Vector2f pos, sf::Vector2f sz) 
		: MovingGameObject()
		, rectShape_{sz}
	{
		rectShape_.setPosition(pos);
		rectShape_.setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		init();
	}
	Bullet::Bullet(sf::Vector2f pos, sf::Vector2f sz, sf::Vector2f d)
		: MovingGameObject(d)
		, rectShape_{sz}
	{
		rectShape_.setPosition(pos);
		rectShape_.setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
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
		rectShape_.setPosition(rectShape_.getPosition() + getDelta());
	}

	sf::Vector2f Bullet::getSize() const
	{
		return rectShape_.getSize();
	}
	void Bullet::setSize(sf::Vector2f sz)
	{
		rectShape_.setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		rectShape_.setSize(sz);
	}

	sf::Vector2f Bullet::getPosition() const
	{
		return rectShape_.getPosition();
	}
	void Bullet::setPosition(sf::Vector2f pos)
	{
		rectShape_.setPosition(pos);
	}

	const sf::IntRect& Bullet::getRect() const
	{
		return rectShape_.getTextureRect();
	}

}