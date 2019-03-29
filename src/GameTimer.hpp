#pragma once
#ifndef GAME_TIMER_HPP
#define GAME_TIMER_HPP

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
		GameTimersDispatcher(){}

		GameTimersDispatcher(const GameTimersDispatcher&) = delete;
		GameTimersDispatcher& operator=(const GameTimersDispatcher&) = delete;

		GameTimersDispatcher(GameTimersDispatcher&&) = delete;
		GameTimersDispatcher& operator=(GameTimersDispatcher&&) = delete;

		void addTimer(GameTimer& tmr) { timers_.push_back(&tmr); }
		void deleteTimer(GameTimer& tmr) { timers_.erase(std::remove(std::begin(timers_), std::end(timers_), &tmr)); }

	private:
		std::vector<GameTimer*> timers_;
		static GameTimersDispatcher* instance_;
	};

	struct GameTimer
	{
		GameTimer() : id_{ timerId_++ } {}
		explicit GameTimer(std::size_t msec) : id_{ timerId_++ } { start(msec);  }
		virtual ~GameTimer() { if(!stopped_) (GameTimersDispatcher::Instance()).deleteTimer(*this); }

		GameTimer(const GameTimer&) = delete;
		GameTimer& operator=(const GameTimer&) = delete;

		GameTimer(GameTimer&&) = delete;
		GameTimer& operator=(GameTimer&&) = delete;

		my::signal<> onTimerCall;

		inline void start() { begin_time_ = std::chrono::steady_clock::now();  }
		void start(std::size_t msec);
		void start(std::chrono::milliseconds msec) { start(msec.count()); }
		void stop();

		inline void setInterval(std::size_t msec) { interval_ = msec; }
		inline void setInterval(std::chrono::milliseconds msec) { setInterval(static_cast<std::size_t>(msec.count())); }

		inline void setSingleShot(bool sshot) { single_ = sshot; }
		inline bool isSingleShot() { return single_; }

		inline bool isStopped() const { return stopped_; }
		inline std::size_t interval() const { return interval_;  }
		inline std::size_t timerId() const { return id_;  }
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