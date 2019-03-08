#pragma once
#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>
#include <algorithm>
#include <mutex>

struct Observable;

struct Observer
{
	virtual void handleEvent(Observable& observ) = 0;
};

struct Observable
{
	void addObserver(Observer& obs)
	{
		std::lock_guard<std::mutex> lock(mtx_);
		observers_.push_back(&obs);
	}
	void delObserver(Observer& obs)
	{
		std::lock_guard<std::mutex> lock(mtx_);
		observers_.erase(std::remove(
			std::begin(observers_), std::end(observers_), &obs
		));
	}
	void notify()
	{
		std::lock_guard<std::mutex> lock(mtx_);
		for(Observer* obs : observers_) {
			obs->handleEvent(*this);
		}
	}
	virtual ~Observable()
	{
	}

private:
	std::vector<Observer*> observers_;
	std::mutex mtx_;
};

#endif // OBSERVER_HPP