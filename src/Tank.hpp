#pragma once
#ifndef TANK_HPP
#define TANK_HPP

#include "MovingGameObject.hpp"
#include "Bullet.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>
#include <array>

namespace tf
{
	struct Tank : MovingGameObject
	{
		explicit Tank(float step = 0.f, float sz = 0.f, sf::Vector2f pos = {0.f, 0.f});
		virtual ~Tank();

		virtual void draw(sf::RenderWindow& win) override;

		virtual float getSize() const override { return (body_.front())->getSize().x; }
		virtual void setSize(float sz) override;

		virtual sf::Vector2f getPosition() const override { return currPos_; }
		virtual void setPosition(sf::Vector2f pos) override { currPos_ = pos; }

		virtual void setFillColor(const sf::Color& color) override;
		virtual sf::Color getFillColor() const override { return (body_.front())->getFillColor(); }

		virtual void setBorderColor(const sf::Color& color) override;
		virtual sf::Color getBorderColor() const override { return (body_.front())->getOutlineColor(); }

		virtual void setDirection(Direction dir) override;

		virtual void makeShot();
		virtual void makeStep() override;

		virtual void turn(Direction dir);

		const std::vector<Bullet*>& getBullets() { return bullets_; }

		virtual void outOfScreenEvent(const sf::RenderWindow& win) override;

		void deleteBullet(GameObject* bullet);

		virtual void handleCollision(GameObject* obj) override;

	protected:
		std::array<sf::RectangleShape*, 6> body_;
		std::vector<Bullet*> bullets_;

	private:
		sf::Vector2f currPos_{};
	};
}

#endif // TANK_HPP