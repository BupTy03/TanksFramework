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
		Tank(std::shared_ptr<sf::RenderWindow> w);
		Tank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz);
		Tank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz, float step);
		virtual ~Tank();

		virtual void draw() override;

		virtual float getSize() const override { return body_[0]->getSize().x; }
		virtual void setSize(float sz) override;

		virtual sf::Vector2f getPosition() const override { return currPos_; }
		virtual void setPosition(sf::Vector2f pos) override { currPos_ = pos; }

		virtual void setFillColor(const sf::Color& color) override;
		virtual sf::Color getFillColor() const override { return body_[0]->getFillColor(); }

		virtual void setBorderColor(const sf::Color& color) override;
		virtual sf::Color getBorderColor() const override { return body_[0]->getOutlineColor(); }

		virtual void setDirection(Direction dir) override;

		virtual void makeShot();
		virtual void makeStep() override;

		virtual void turn(Direction dir);

		const std::vector<Bullet*>& getBullets() { return bullets_; }

		virtual void outOfScreenEvent() override;

		void deleteBullet(GameObject* bullet);

	protected:
		std::vector<sf::RectangleShape*> body_;
		std::vector<Bullet*> bullets_;
	private:
		sf::Vector2f currPos_{};
	};
}

#endif // TANK_HPP