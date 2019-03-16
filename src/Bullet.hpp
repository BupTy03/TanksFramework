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
		Bullet(std::shared_ptr<sf::RenderWindow> w);
		Bullet(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz);
		Bullet(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz, float step);
		virtual ~Bullet();

		virtual void draw() override;
		virtual void makeStep() override;

		virtual float getSize() const override;
		virtual void setSize(float sz) override;

		virtual sf::Vector2f getPosition() const override;
		virtual void setPosition(sf::Vector2f pos) override;

		virtual void outOfScreenEvent() override;

	private:
		sf::RectangleShape rectShape_;
		GameTimer* moveTimer_{nullptr};
	};
}

#endif // BULLET_HPP