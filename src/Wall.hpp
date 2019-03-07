#pragma once
#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

namespace tf
{

	struct Wall
	{
		virtual ~Wall();

		virtual void setSize(sf::Vector2u sz);
		virtual void draw(sf::RenderWindow& win);
		const sf::IntRect& getTextureRect();
	};

}

#endif // WALL_HPP