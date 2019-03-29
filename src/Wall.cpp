#include "Wall.hpp"

namespace tf
{

	Wall::Wall(std::shared_ptr<sf::RenderWindow> w)
		: GameObject(std::move(w))
	{
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
	}

	Wall::Wall(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos)
		: GameObject(std::move(w))
	{
		rectShape_.setPosition(pos);
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
	}

	Wall::Wall(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, sf::Vector2f sz)
		: GameObject(std::move(w)) 
		, rectShape_(sz)
	{
		rectShape_.setPosition(pos);
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
	}

	void Wall::setSize(float sz)
	{
		rectShape_.setOutlineThickness(-sz / 9.f);
		rectShape_.setSize({sz, sz});
	}

}