#include "GameTimer.hpp"

namespace tf
{

	//	GameTimersDispatcher

	GameTimersDispatcher* GameTimersDispatcher::Instance()
	{
		if (instance_ == nullptr)
		{
			instance_ = new GameTimersDispatcher();
		}

		return instance_;
	}

	GameTimersDispatcher::~GameTimersDispatcher()
	{
		if (instance_ != nullptr) {
			instance_->mainThread_.join();
			delete instance_;
		}
	}

	void GameTimersDispatcher::addTimer(GameTimer& tmr)
	{
		std::lock_guard<std::mutex> lock(mtx_);
		timers_.push_back(&tmr);
	}

	void GameTimersDispatcher::deleteTimer(GameTimer& tmr)
	{
		std::lock_guard<std::mutex> lock(mtx_);
		timers_.erase(std::remove(std::begin(timers_), std::end(timers_), &tmr));
	}

	GameTimersDispatcher::GameTimersDispatcher() : mainThread_([this]()
	{
		while (true) {
			std::lock_guard<std::mutex> lock(mtx_);
			auto first = std::begin(timers_);
			auto last = std::end(timers_);
			while (first != last) {
				GameTimer* curr = *first;
				++first;
				if (!curr->stopped_) {
					//int diff = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - curr->begin_time_)).count();
					if (curr->elapsed() >= curr->interval_) {
						curr->notify();
						if (curr->single_){
							curr->stopped_ = true;
							timers_.erase(std::remove(std::begin(timers_), std::end(timers_), curr));
						}
						else {
							curr->begin_time_ = std::chrono::steady_clock::now();
						}
					}
				}
			}
			std::this_thread::sleep_for(std::chrono::microseconds(500));
		}
	})
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
			(GameTimersDispatcher::Instance())->deleteTimer(*this); 
		}
	}

	void GameTimer::start() 
	{ 
		begin_time_ = std::chrono::steady_clock::now(); 
	}

	void GameTimer::start(std::size_t msec)
	{
		if(stopped_) {
			(GameTimersDispatcher::Instance())->addTimer(*this);
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
		(GameTimersDispatcher::Instance())->deleteTimer(*this);
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