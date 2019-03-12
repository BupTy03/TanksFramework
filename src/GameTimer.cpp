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

	void GameTimersDispatcher::addTimer(GameTimer& tmr)
	{
		timers_.push_back(&tmr);
	}

	void GameTimersDispatcher::deleteTimer(GameTimer& tmr)
	{
		timers_.erase(std::remove(std::begin(timers_), std::end(timers_), &tmr));
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

	GameTimersDispatcher::GameTimersDispatcher()
	{
	}

	GameTimersDispatcher* GameTimersDispatcher::instance_ = nullptr;

	//	end of GameTimersDispatcher


	//	GameTimer

	GameTimer::GameTimer() : id_{ timerId_++ } {}
	GameTimer::GameTimer(std::size_t msec) : id_{ timerId_++ }
	{ 
		start(msec); 
	}

	GameTimer::~GameTimer() 
	{ 
		if(!stopped_){
			(GameTimersDispatcher::Instance()).deleteTimer(*this);
		}
	}

	void GameTimer::start() 
	{ 
		begin_time_ = std::chrono::steady_clock::now(); 
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

	void GameTimer::start(std::chrono::milliseconds msec)
	{
		start(msec.count());
	}

	void GameTimer::stop()
	{
		stopped_ = true;
		end_time_ = std::chrono::steady_clock::now();
		(GameTimersDispatcher::Instance()).deleteTimer(*this);
	}

	bool GameTimer::isStopped() const
	{
		return stopped_;
	}

	void GameTimer::setInterval(std::size_t msec)
	{
		interval_ = msec;
	}
	void GameTimer::setInterval(std::chrono::milliseconds msec)
	{
		setInterval(static_cast<std::size_t>(msec.count()));
	}

	void GameTimer::setSingleShot(bool sshot)
	{
		single_ = sshot;
	}

	bool GameTimer::isSingleShot()
	{
		return single_;
	}

	std::size_t GameTimer::interval() const 
	{ 
		return interval_; 
	}

	std::size_t GameTimer::timerId() const
	{ 
		return id_; 
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