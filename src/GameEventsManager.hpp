#pragma once
#ifndef GAME_EVENTS_MANAGER_HPP
#define GAME_EVENTS_MANAGER_HPP

#include "GameObject.hpp"

#include <vector>

namespace tf
{

	struct GameEventsManager
	{
		static GameEventsManager& Instance();
		virtual ~GameEventsManager();
	private:
		GameEventsManager();
		void processEvents();

	private:
		static GameEventsManager* instance_;
		std::vector<GameObject*> objects_;
	};

} // tf

#endif // GAME_EVENTS_MANAGER_HPP