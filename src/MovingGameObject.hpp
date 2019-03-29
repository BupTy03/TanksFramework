#pragma once
#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

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

	struct MovingGameObject : GameObject
	{
		MovingGameObject(std::shared_ptr<sf::RenderWindow> w);
		MovingGameObject(std::shared_ptr<sf::RenderWindow> w, float step);
		virtual ~MovingGameObject(){}

		virtual void makeStep() = 0;

		inline float getStep() { return step_; }
		virtual void setStep(float step) { step_ = step; }

		inline Direction getDirection() { return dir_; }
		virtual void setDirection(Direction dir) { dir_ = dir; }

		virtual void outOfScreenEvent() override;

	private:
		Direction dir_{};
		float step_{};
	};

}

#endif // MOVING_OBJECT_HPP