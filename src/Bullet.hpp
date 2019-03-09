#pragma once
#ifndef BULLET_HPP
#define BULLET_HPP

#include "MovingGameObject.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

namespace tf
{
	struct Bullet : MovingGameObject
	{
		Bullet();
		Bullet(sf::Vector2f pos);
		virtual ~Bullet();

		virtual void draw(sf::RenderWindow& w) override;
		virtual bool intersects(const GameObject& other) const override;

		virtual sf::Vector2f getSize() const override;
		virtual void setSize(sf::Vector2f sz) override;

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(sf::Vector2f pos) override;

		virtual const sf::IntRect& getRect() const override;

		virtual void makeStep() override;
		virtual void turn() override;

		virtual void handleEvent(Observable& observ) override;

	private:
		sf::RectangleShape rectShape_;
	};
}

#endif // BULLET_HPP