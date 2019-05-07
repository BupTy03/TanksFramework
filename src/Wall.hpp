#ifndef WALL_HPP
#define WALL_HPP

#include "GameObject.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

namespace tf
{

	struct Wall : GameObject
	{
		explicit Wall(sf::Vector2f sz = {0.f, 0.f}, sf::Vector2f pos = {0.f, 0.f});
		virtual ~Wall(){ delete rectShape_; }

		virtual float getSize() const override { return rectShape_->getSize().x; }
		virtual void setSize(float sz) override;

		virtual sf::Vector2f getPosition() const override { return rectShape_->getPosition(); }
		virtual void setPosition(sf::Vector2f pos) override { rectShape_->setPosition(pos); }

		virtual void draw(sf::RenderWindow& win) override { win.draw(*rectShape_); }

		virtual void setFillColor(const sf::Color& color) { rectShape_->setFillColor(color); }
		virtual sf::Color getFillColor() const { return rectShape_->getFillColor(); }

		virtual void setBorderColor(const sf::Color& color) { rectShape_->setOutlineColor(color); }
		virtual sf::Color getBorderColor() const { return rectShape_->getOutlineColor(); }

		virtual void handleCollision(GameObject* obj) override;

	protected:
		sf::RectangleShape* rectShape_{nullptr};
	};

}

#endif // WALL_HPP