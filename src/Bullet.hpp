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
		explicit Bullet(std::shared_ptr<sf::RenderWindow> w);
		explicit Bullet(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz);
		explicit Bullet(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz, float step);
		virtual ~Bullet(){ delete moveTimer_; }

		virtual void draw() override{ win_->draw(rectShape_); }
		virtual void makeStep() override;

		virtual float getSize() const override { return rectShape_.getSize().x; }
		virtual void setSize(float sz) override;

		virtual sf::Vector2f getPosition() const override { return rectShape_.getPosition(); }
		virtual void setPosition(sf::Vector2f pos) override { rectShape_.setPosition(pos); }

		virtual void setFillColor(const sf::Color& color) override { rectShape_.setFillColor(color); }
		virtual sf::Color getFillColor() const override { return rectShape_.getFillColor(); }

		virtual void setBorderColor(const sf::Color& color) override { rectShape_.setOutlineColor(color); }
		virtual sf::Color getBorderColor() const override { return rectShape_.getOutlineColor(); }

		virtual void outOfScreenEvent() override { deleteLater(); }

		virtual void handleCollision(GameObject* obj) override;

	private:
		sf::RectangleShape rectShape_;
		GameTimer* moveTimer_{nullptr};
	};
}

#endif // BULLET_HPP