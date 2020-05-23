#pragma once

#include "GameObject.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>


namespace tf
{

	class Wall : public GameObject
	{
	public:
		explicit Wall(
			const sf::Vector2f& sz = sf::Vector2f{0.f, 0.f}, 
			const sf::Vector2f& pos = sf::Vector2f{0.f, 0.f}
		);

		float getSize() const override;
		void setSize(float sz) override;

		sf::Vector2f getPosition() const override;
		void setPosition(const sf::Vector2f& pos) override;

		void draw(sf::RenderWindow& win) override;

		virtual void setFillColor(const sf::Color& color);
		virtual sf::Color getFillColor() const;

		virtual void setBorderColor(const sf::Color& color);
		virtual sf::Color getBorderColor() const;

		void handleCollision(GameObject* obj) override;

	protected:
		const sf::RectangleShape& getRectShape() const;

	private:
		sf::RectangleShape rectShape_;
	};

}
