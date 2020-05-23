#include "GameTimer.hpp"


namespace tf
{

	//	GameTimersDispatcher

	GameTimersDispatcher& GameTimersDispatcher::Instance()
	{
		static GameTimersDispatcher instance_;
		return instance_;
	}

	void GameTimersDispatcher::dispatch()
	{
		for(auto timer : timers_) {
			if (!timer->isStopped() && timer->elapsed() >= timer->interval()) {
				timer->onTimerCall();
				if(timer->isSingleShot()) {
					timer->stop();
				}
				else {
					timer->start();
				}
			}
		}
	}

	//	end of GameTimersDispatcher


	//	GameTimer

	GameTimer::GameTimer()
		: begin_time_{}
		, end_time_{}
		, interval_{0}
		, single_{false}
		, stopped_{true}
		, id_{timerId_++}
	{}

	GameTimer::GameTimer(std::chrono::milliseconds msec)
		: begin_time_{}
		, end_time_{}
		, interval_{0}
		, single_{false}
		, stopped_{true}
		, id_{timerId_++}
	{
		start(msec);
	}

	GameTimer::~GameTimer() 
	{ 
		if(!stopped_) 
			(GameTimersDispatcher::Instance()).deleteTimer(*this); 
	}

	void GameTimer::start(std::size_t msec)
	{
		if(stopped_) {
			(GameTimersDispatcher::Instance()).addTimer(*this);
		}

		interval_ = msec;
		stopped_ = false;
		begin_time_ = std::chrono::steady_clock::now();
	}

	void GameTimer::stop()
	{
		stopped_ = true;
		end_time_ = std::chrono::steady_clock::now();
		(GameTimersDispatcher::Instance()).deleteTimer(*this);
	}

	std::size_t GameTimer::elapsed() const 
	{
		if (stopped_) {
			return std::chrono::duration_cast<std::chrono::milliseconds>(end_time_ - begin_time_).count();
		}
		
		return static_cast<std::size_t>(
			std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin_time_)
			.count()
		);
	}

	std::size_t GameTimer::timerId_ = 1;

	//	end of GameTimer

}
