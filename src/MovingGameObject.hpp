#pragma once

#include "GameObject.hpp"
#include "GameTimer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <random>


namespace tf
{

	enum class Direction
	{
		FORWARD,	
		BACKWARD,	
		LEFT,		
		RIGHT, 			
		FORWARD_LEFT, 	
		FORWARD_RIGHT, 	
		BACKWARD_LEFT, 	
		BACKWARD_RIGHT, 	
		STOPPED,			
	};

	class MovingGameObject : public GameObject
	{
	public:
		explicit MovingGameObject(GameObjectType type);

		virtual void makeStep() = 0;

		float getStep() const;
		virtual void setStep(float step);

		Direction getDirection() const;
		virtual void setDirection(Direction dir);

		void outOfScreenEvent(const sf::RenderWindow& win) override;

	private:
		Direction dir_;
		float step_;
	};

}
