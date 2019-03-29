#include "GameTimer.hpp"

namespace tf
{

	//	GameTimersDispatcher

	GameTimersDispatcher& GameTimersDispatcher::Instance()
	{
		if (instance_ == nullptr) {
			instance_ = new GameTimersDispatcher();
		}
		return *instance_;
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

	GameTimersDispatcher* GameTimersDispatcher::instance_ = nullptr;

	//	end of GameTimersDispatcher


	//	GameTimer

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