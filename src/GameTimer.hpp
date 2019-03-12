#pragma once
#ifndef GAME_TIMER_HPP
#define GAME_TIMER_HPP

#include "Observer.hpp"
#include "signal.hpp"

#include <vector>
#include <chrono>
#include <algorithm>

namespace tf
{
	struct GameTimer;

	struct GameTimersDispatcher
	{
		friend class GameTimer;

		static GameTimersDispatcher& Instance();
		void dispatch();

	private:
		GameTimersDispatcher();

		GameTimersDispatcher(const GameTimersDispatcher&) = delete;
		GameTimersDispatcher& operator=(const GameTimersDispatcher&) = delete;

		GameTimersDispatcher(GameTimersDispatcher&&) = delete;
		GameTimersDispatcher& operator=(GameTimersDispatcher&&) = delete;

		void addTimer(GameTimer& tmr);
		void deleteTimer(GameTimer& tmr);

	private:
		std::vector<GameTimer*> timers_;
		static GameTimersDispatcher* instance_;
	};

	struct GameTimer
	{
		GameTimer();
		explicit GameTimer(std::size_t msec);
		~GameTimer();

		GameTimer(const GameTimer&) = delete;
		GameTimer& operator=(const GameTimer&) = delete;

		GameTimer(GameTimer&&) = delete;
		GameTimer& operator=(GameTimer&&) = delete;

		my::signal<> onTimerCall;

		void start();
		void start(std::size_t msec);
		void start(std::chrono::milliseconds msec);
		void stop();

		void setInterval(std::size_t msec);
		void setInterval(std::chrono::milliseconds msec);

		void setSingleShot(bool sshot);
		bool isSingleShot();

		bool isStopped() const;
		std::size_t interval() const;
		std::size_t timerId() const;
		std::size_t elapsed() const;

	private:
		std::chrono::steady_clock::time_point begin_time_;
		std::chrono::steady_clock::time_point end_time_;
		std::size_t interval_{};
		bool single_{false};
		bool stopped_{true};
		std::size_t id_{};
		static std::size_t timerId_;
	};
}

#endif // GAME_TIMER_HPP