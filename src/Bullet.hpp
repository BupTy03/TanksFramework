#pragma once

#include "MovingGameObject.hpp"

#include <SFML/Graphics/RectangleShape.hpp>


class RenderWindow;

namespace tf
{
	class Bullet : public MovingGameObject
	{
	public:
		explicit Bullet(
			float step, 
			float sz, 
			const sf::Vector2f& pos
		);

		void draw(sf::RenderWindow& win) override;
		void makeStep() override;

		float getSize() const override;
		void setSize(float sz) override;

		sf::Vector2f getPosition() const override;
		void setPosition(const sf::Vector2f& pos) override;

		void setFillColor(const sf::Color& color) override;
		sf::Color getFillColor() const override;

		void setBorderColor(const sf::Color& color) override;
		sf::Color getBorderColor() const override;

		void outOfScreenEvent(const sf::RenderWindow& win);

	private:
		sf::RectangleShape rectShape_;
		GameTimer moveTimer_;
	};
}
