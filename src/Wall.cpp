#include "Wall.hpp"

namespace tf
{

	Wall::Wall()
		: GameObject(GameObjectType::WALL)
	{
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
	}

	Wall::Wall(sf::Vector2f pos)
		: GameObject(GameObjectType::WALL)
	{
		rectShape_.setPosition(pos);
		rectShape_.setFillColor(sf::Color(62, 64, 55));
		rectShape_.setOutlineColor(sf::Color(107, 109, 99));
	}

	Wall::Wall(sf::Vector2f pos, sf::Vector2f sz)
		: GameObject(GameObjectType::WALL) 
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