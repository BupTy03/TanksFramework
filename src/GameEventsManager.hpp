#pragma once
#ifndef GAME_EVENTS_MANAGER_HPP
#define GAME_EVENTS_MANAGER_HPP

#include "GameObject.hpp"

#include <SFML/System/Vector2.hpp>

#include <vector>

namespace tf
{

	struct GameEventsManager
	{
		static GameEventsManager& Instance();
		virtual ~GameEventsManager();

		void setWindow(std::shared_ptr<sf::RenderWindow> w);

		void addGameObject(GameObject* obj);
		void removeGameObject(GameObject* obj);

		void processEvents();

		std::size_t countObjects();

	private:
		GameEventsManager();
		void collectDeleted();
		void processOutOfScreenEvents();
		void handleKeyEvents(sf::Keyboard::Key key);

	private:
		static GameEventsManager* instance_;
		std::vector<GameObject*> objects_;
		std::shared_ptr<sf::RenderWindow> window_;
	};

} // tf

#endif // GAME_EVENTS_MANAGER_HPP