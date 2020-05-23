#include "Bullet.hpp"
#include "Wall.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


namespace tf
{

	Bullet::Bullet(float step, float sz, const sf::Vector2f& pos)
		: MovingGameObject(GameObjectType::BULLET)
		, rectShape_{sf::Vector2f{sz, sz}}
		, moveTimer_()
	{
		setStep(step);

		rectShape_.setPosition(pos);
		rectShape_.setOutlineThickness(-sz / 9.f);
		rectShape_.setFillColor(sf::Color{220, 20, 60});
		rectShape_.setOutlineColor(sf::Color{144, 0, 32});
		moveTimer_.onTimerCall.connect(this, &Bullet::makeStep);
		moveTimer_.start(100);
	}

	void Bullet::draw(sf::RenderWindow& win) 
	{
		win.draw(rectShape_);
	}

	void Bullet::makeStep()
	{
		const auto ps = getPosition();
		const auto step = getStep();
		switch (getDirection())
		{
			case Direction::FORWARD:
				setPosition(sf::Vector2f{ps.x, ps.y - step});
				break;
			case Direction::BACKWARD:
				setPosition(sf::Vector2f{ps.x, ps.y + step});
				break;
			case Direction::LEFT:
				setPosition(sf::Vector2f{ps.x - step, ps.y});
				break;
			case Direction::RIGHT:
				setPosition(sf::Vector2f{ps.x + step, ps.y});
				break;
			default:
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
		rectShape_.setSize(sf::Vector2f{sz, sz});
	}

	sf::Vector2f Bullet::getPosition() const 
	{ 
		return rectShape_.getPosition(); 
	}

	void Bullet::setPosition(const sf::Vector2f& pos) 
	{ 
		rectShape_.setPosition(pos); 
	}

	void Bullet::setFillColor(const sf::Color& color) 
	{ 
		rectShape_.setFillColor(color); 
	}

	sf::Color Bullet::getFillColor() const 
	{ 
		return rectShape_.getFillColor(); 
	}

	void Bullet::setBorderColor(const sf::Color& color) 
	{ 
		rectShape_.setOutlineColor(color); 
	}

	sf::Color Bullet::getBorderColor() const 
	{ 
		return rectShape_.getOutlineColor(); 
	}

	void Bullet::outOfScreenEvent(const sf::RenderWindow& win) 
	{ 
		deleteLater(); 
	}

}
