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
		Tank(sf::Vector2f pos);
		virtual ~Tank();

		virtual void draw(sf::RenderWindow& w) override;
		virtual bool intersects(const GameObject& other) const override;

		virtual sf::Vector2f getSize() const override;
		virtual void setSize(sf::Vector2f sz) override;

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(sf::Vector2f pos) override;

		virtual const sf::IntRect& getRect() const override;

		virtual void makeShot();

		virtual void makeStep() override;
		virtual void turn() override;

		virtual void handleEvent(Observable& observ) override;

	protected:
		std::vector<sf::RectangleShape*> body_;
		std::vector<Bullet*> bullets_;
	};
}

#endif // TANK_HPP