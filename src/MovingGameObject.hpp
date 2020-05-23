#pragma once

#include "Direction.hpp"
#include "GameTimer.hpp"
#include "GameObject.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <random>
#include <stdexcept>


namespace tf
{

	class MovingGameObject : public GameObject
	{
	public:
		explicit MovingGameObject(GameObjectType type);

		virtual void makeStep() = 0;

		float getStep() const;
		virtual void setStep(float step);

		Direction getDirection() const;
		virtual void setDirection(const Direction& dir);

		void outOfScreenEvent(const sf::RenderWindow& win) override;

	private:
		Direction dir_;
		float step_;
	};

}
