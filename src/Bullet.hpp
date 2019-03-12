#pragma once
#ifndef BULLET_HPP
#define BULLET_HPP

#include "MovingGameObject.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace tf
{
	struct Bullet : MovingGameObject
	{
		Bullet();
		Bullet(sf::Vector2f pos, sf::Vector2f sz);
		Bullet(sf::Vector2f pos, sf::Vector2f sz, sf::Vector2f d);
		virtual ~Bullet();

		virtual void draw(sf::RenderWindow& w) override;
		virtual void makeStep() override;

		virtual sf::Vector2f getSize() const override;
		virtual void setSize(sf::Vector2f sz) override;

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(sf::Vector2f pos) override;

		virtual const sf::IntRect& getRect() const override;

	private:
		void init();
		sf::RectangleShape rectShape_;
	};
}

#endif // BULLET_HPP