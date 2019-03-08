#include "Wall.hpp"

namespace tf
{

	Wall::Wall(const sf::Vector2f& pos, float sz)
			: rectShape_(sf::Vector2f(sz, sz))
	{
		rectShape_.setPosition(pos);
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineThickness(-sz / 6.f);
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
		rectShape_.setTextureRect(
			sf::IntRect(static_cast<int>(pos.x), static_cast<int>(pos.y), 
						static_cast<int>(sz), static_cast<int>(sz))
		);
	}

	const sf::Vector2f& Wall::getSize() const
	{
		return rectShape_.getSize();
	}
	void Wall::setSize(const sf::Vector2f& sz)
	{
		rectShape_.setSize(sz);
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