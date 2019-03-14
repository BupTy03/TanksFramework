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
		Tank(sf::Vector2f pos, float sz);
		Tank(sf::Vector2f pos, float sz, float step);
		virtual ~Tank();

		virtual void draw(sf::RenderWindow& w) override;

		virtual float getSize() const override;
		virtual void setSize(float sz) override;

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(sf::Vector2f pos) override;

		virtual void setDirection(Direction dir) override;
		virtual void setRandDirection();

		virtual void makeShot();
		virtual void makeStep() override;

		virtual void turn(Direction dir);

		const std::vector<Bullet*>& getBullets();

		virtual void outOfScreenEvent() override;

	protected:
		sf::Vector2f currPos_{};
		GameTimer* changeDirectionTimer_{nullptr};
		std::vector<sf::RectangleShape*> body_;
		std::vector<Bullet*> bullets_;
		std::default_random_engine randEngine_;
	};
}

#endif // TANK_HPP