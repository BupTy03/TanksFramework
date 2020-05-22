#pragma once

#include "slot.hpp"

#include <utility>
#include <algorithm>
#include <vector>
#include <mutex>
#include <shared_mutex>

namespace my
{
	template<class... Args>
	struct signal
	{
		void operator()(Args&&... args)
		{
			std::size_t sz = slots_.size();
			for (std::size_t i = 0; i < sz; ++i) {
				slots_[i](std::forward<Args>(args)...);
				if(slots_.size() < sz) { // if slot contains code that unsubscribe him
					sz = slots_.size();
					i--;
				}
			}
		}

		void connect(void(*func)(Args...))
		{
			if (func == nullptr) return;
			connect(slot<Args...>(func));
		}

		template<class Obj>
		void connect(Obj* obj, void (Obj::* func)(Args...))
		{
			if (obj == nullptr || func == nullptr) return;
			connect(slot<Args...>(obj, func));
		}

		void connect(const slot<Args...>& sl)
		{
			if (std::find(std::cbegin(slots_), std::cend(slots_), sl) != std::cend(slots_))
				return;

			slots_.push_back(sl);
		}

		void connect(slot<Args...>&& sl)
		{
			if (std::find(std::cbegin(slots_), std::cend(slots_), sl) != std::cend(slots_))
				return;

			slots_.push_back(std::move(sl));
		}

		void disconnect(void(*func)(Args...))
		{
			if (func == nullptr) return;
			disconnect(slot<Args...>(func));
		}

		template<class Obj, class... FArgs>
		void disconnect(Obj* obj, void (Obj::* func)(FArgs...))
		{
			disconnect(slot<FArgs...>(obj, func));
		}

		void disconnect(const slot<Args...>& sl)
		{
			slots_.erase(std::find(std::begin(slots_), std::end(slots_), sl));
		}

	private:
		std::vector<slot<Args...>> slots_;
	};

}
