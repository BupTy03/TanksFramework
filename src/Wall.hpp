#pragma once
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
		Wall(std::shared_ptr<sf::RenderWindow> w);
		Wall(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f sz);
		Wall(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, sf::Vector2f sz);
		virtual ~Wall(){}

		virtual float getSize() const override { return rectShape_.getSize().x; }
		virtual void setSize(float sz) override;

		virtual sf::Vector2f getPosition() const override { return rectShape_.getPosition(); }
		virtual void setPosition(sf::Vector2f pos) override { rectShape_.setPosition(pos); }

		virtual void draw() override { win_->draw(rectShape_); }

	protected:
		sf::RectangleShape rectShape_;
	};

}

#endif // WALL_HPP