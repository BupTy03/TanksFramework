#include "Wall.hpp"

namespace tf
{

	Wall::Wall()
	{
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
	}

	Wall::Wall(sf::Vector2f pos)
	{
		rectShape_.setPosition(pos);
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
	}

	Wall::Wall(sf::Vector2f pos, sf::Vector2f sz)
		: rectShape_(sz)
	{
		rectShape_.setPosition(pos);
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
	}

	sf::Vector2f Wall::getSize() const
	{
		return rectShape_.getSize();
	}
	void Wall::setSize(sf::Vector2f sz)
	{
		rectShape_.setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		rectShape_.setSize(sz);
	}

	sf::Vector2f Wall::getPosition() const
	{
		return rectShape_.getPosition();
	}
	void Wall::setPosition(sf::Vector2f pos)
	{
		rectShape_.setPosition(pos);
	}

	void Wall::draw(sf::RenderWindow& win)
	{
		win.draw(rectShape_);
	}
	bool Wall::intersects(const GameObject& other) const
	{
		return (getRect()).intersects(other.getRect());
	}

	const sf::IntRect& Wall::getRect() const
	{
		return rectShape_.getTextureRect();
	}

}