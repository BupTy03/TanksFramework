#pragma once
#ifndef WALL_HPP
#define WALL_HPP

#include "GameObject.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

namespace tf
{

	struct Wall : GameObject
	{
		Wall();
		Wall(sf::Vector2f sz);
		Wall(sf::Vector2f pos, sf::Vector2f sz);

		virtual sf::Vector2f getSize() const override;
		virtual void setSize(sf::Vector2f sz) override;

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(sf::Vector2f pos) override;

		virtual void draw(sf::RenderWindow& win) override;
		virtual bool intersects(const GameObject& other) const override;
		virtual const sf::IntRect& getRect() const override;

	protected:
		sf::RectangleShape rectShape_;
	};

}

#endif // WALL_HPP