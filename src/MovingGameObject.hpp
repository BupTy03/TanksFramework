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
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	struct MovingGameObject : Observer, GameObject
	{
		MovingGameObject();
		virtual ~MovingGameObject();

		virtual void makeStep() = 0;
		virtual void turn() = 0;

		std::size_t getStep();
		virtual void setStep(std::size_t step);

		Direction getDirection();
		virtual void setDirection(Direction dir);

		void startTimer();
		void startTimer(std::size_t msec);
		void startTimer(std::chrono::milliseconds msec);
		void stopTimer();

		void setTimerInterval(std::size_t msec);
		void setTimerInterval(std::chrono::milliseconds msec);

		void setTimerSingleShot(bool sshot);
		bool isTimerSingleShot();

		virtual void handleEvent(Observable& observ) override;

	private:
		std::size_t step_{};
		GameTimer* timer_{nullptr};
		Direction dir_{Direction::FORWARD};
	};

}

#endif // MOVING_OBJECT_HPP