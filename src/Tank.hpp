#pragma once

#include "MovingGameObject.hpp"
#include "Bullet.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include <vector>
#include <array>


namespace tf
{
	class Tank : public MovingGameObject
	{
	public:
		Tank();

		void draw(sf::RenderWindow& win) override;

		float getSize() const override;
		void setSize(float sz) override;

		sf::Vector2f getPosition() const override;
		void setPosition(const sf::Vector2f& pos) override;

		void setFillColor(const sf::Color& color) override;
		sf::Color getFillColor() const override;

		void setBorderColor(const sf::Color& color) override;
		sf::Color getBorderColor() const override;

		void setDirection(Direction dir) override;

		virtual void makeShot();
		void makeStep() override;

		virtual void turn(Direction dir);

		const std::vector<Bullet*>& getBullets() const;

		void outOfScreenEvent(const sf::RenderWindow& win) override;

		void deleteBullet(GameObject* bullet);

		void handleCollision(GameObject* obj) override;

	protected:
		std::array<sf::RectangleShape, 6> body_;
		std::vector<Bullet*> bullets_;

	private:
		sf::Vector2f currPos_;
	};
}
