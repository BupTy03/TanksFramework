#pragma once
#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

#include "GameObject.hpp"
#include "Observer.hpp"
#include "GameTimer.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace tf
{

	enum class Direction
	{
		FORWARD 		= 0,
		BACKWARD 		= 1,
		LEFT 			= 2,
		RIGHT 			= 3,
		FORWARD_LEFT 	= 4,
		FORWARD_RIGHT 	= 5,
		BACKWARD_LEFT 	= 6,
		BACKWARD_RIGHT 	= 7
	};

	struct MovingGameObject : GameObject
	{
		MovingGameObject();
		MovingGameObject(sf::Vector2f d);
		virtual ~MovingGameObject();

		virtual void makeStep() = 0;

		sf::Vector2f getDelta();
		void setDelta(sf::Vector2f d);

		virtual void changeDirection(Direction dir);

		static Direction getRandomDirection(Direction from, Direction to);

		void startTimer();
		void startTimer(std::size_t msec);
		void startTimer(std::chrono::milliseconds msec);
		void stopTimer();

		void setTimerInterval(std::size_t msec);
		void setTimerInterval(std::chrono::milliseconds msec);

		void setTimerSingleShot(bool sshot);
		bool isTimerSingleShot();

	protected:
		GameTimer* timer_{nullptr};
	private:
		sf::Vector2f d_;
	};

}

#endif // MOVING_OBJECT_HPP