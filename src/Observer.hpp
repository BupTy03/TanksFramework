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
	virtual void addObserver(Observer& obs)
	{
		observers_.push_back(&obs);
	}
	virtual void delObserver(Observer& obs)
	{
		observers_.erase(std::remove(
			std::begin(observers_), std::end(observers_), &obs
		));
	}
	virtual void notify()
	{
		for(auto obs : observers_) {
			obs->handleEvent(*this);
		}
	}
	virtual ~Observable()
	{
	}

private:
	std::vector<Observer*> observers_;
};

#endif // OBSERVER_HPP