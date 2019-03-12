#pragma once
#ifndef TANK_HPP
#define TANK_HPP

#include "MovingGameObject.hpp"
#include "Bullet.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>

namespace tf
{
	struct Tank : MovingGameObject
	{
		Tank();
		Tank(sf::Vector2f pos, sf::Vector2f sz);
		Tank(sf::Vector2f pos, sf::Vector2f sz, sf::Vector2f d);
		virtual ~Tank();

		virtual void draw(sf::RenderWindow& w) override;

		virtual sf::Vector2f getSize() const override;
		virtual void setSize(sf::Vector2f sz) override;

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(sf::Vector2f pos) override;

		virtual void makeShot();
		virtual void makeStep() override;

		const std::vector<Bullet*>& getBullets();

	protected:
		std::vector<sf::RectangleShape*> body_;
		std::vector<Bullet*> bullets_;
	};
}

#endif // TANK_HPP