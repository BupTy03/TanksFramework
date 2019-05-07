#ifndef BULLET_HPP
#define BULLET_HPP

#include "MovingGameObject.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace tf
{
	struct Bullet : MovingGameObject
	{
		explicit Bullet(float step = 0.f, float sz = 0.f, sf::Vector2f pos = {0.f, 0.f});
		virtual ~Bullet();

		virtual void draw(sf::RenderWindow& win) override{ win.draw(*rectShape_); }
		virtual void makeStep() override;

		virtual float getSize() const override { return rectShape_->getSize().x; }
		virtual void setSize(float sz) override;

		virtual sf::Vector2f getPosition() const override { return rectShape_->getPosition(); }
		virtual void setPosition(sf::Vector2f pos) override { rectShape_->setPosition(pos); }

		virtual void setFillColor(const sf::Color& color) override { rectShape_->setFillColor(color); }
		virtual sf::Color getFillColor() const override { return rectShape_->getFillColor(); }

		virtual void setBorderColor(const sf::Color& color) override { rectShape_->setOutlineColor(color); }
		virtual sf::Color getBorderColor() const override { return rectShape_->getOutlineColor(); }

		virtual void outOfScreenEvent(const sf::RenderWindow& win) override { deleteLater(); }

	private:
		sf::RectangleShape* rectShape_{nullptr};
		GameTimer* moveTimer_{nullptr};
	};
}

#endif // BULLET_HPP