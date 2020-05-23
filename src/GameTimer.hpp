#pragma once

#include "signal.hpp"

#include <vector>
#include <chrono>
#include <algorithm>


namespace tf
{
	class GameTimer;

	class GameTimersDispatcher
	{
	public:
		friend class GameTimer;

		static GameTimersDispatcher& Instance();
		void dispatch();

	private:
		GameTimersDispatcher() = default;

		GameTimersDispatcher(const GameTimersDispatcher&) = delete;
		GameTimersDispatcher& operator=(const GameTimersDispatcher&) = delete;

		GameTimersDispatcher(GameTimersDispatcher&&) = delete;
		GameTimersDispatcher& operator=(GameTimersDispatcher&&) = delete;

		void addTimer(GameTimer& tmr) { timers_.push_back(&tmr); }
		void deleteTimer(GameTimer& tmr) { timers_.erase(std::remove(std::begin(timers_), std::end(timers_), &tmr)); }

	private:
		std::vector<GameTimer*> timers_;
	};

	class GameTimer
	{
	public:
		GameTimer();
		explicit GameTimer(std::chrono::milliseconds msec);
		virtual ~GameTimer();

		GameTimer(const GameTimer&) = delete;
		GameTimer& operator=(const GameTimer&) = delete;

		GameTimer(GameTimer&&) = delete;
		GameTimer& operator=(GameTimer&&) = delete;

		my::signal<> onTimerCall;

		void start() { begin_time_ = std::chrono::steady_clock::now();  }
		void start(std::size_t msec);
		void start(std::chrono::milliseconds msec) { start(msec.count()); }
		void stop();

		void setInterval(std::size_t msec) { interval_ = msec; }
		void setInterval(std::chrono::milliseconds msec) { setInterval(static_cast<std::size_t>(msec.count())); }

		void setSingleShot(bool sshot) { single_ = sshot; }
		bool isSingleShot() { return single_; }

		bool isStopped() const { return stopped_; }
		std::size_t interval() const { return interval_;  }
		std::size_t timerId() const { return id_;  }
		std::size_t elapsed() const;

	private:
		std::chrono::steady_clock::time_point begin_time_;
		std::chrono::steady_clock::time_point end_time_;
		std::size_t interval_;
		bool single_;
		bool stopped_;
		std::size_t id_;
		static std::size_t timerId_;
	};
}
