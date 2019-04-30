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

		inline void setWindow(std::shared_ptr<sf::RenderWindow> w){ window_ = std::move(w); }

		void addGameObject(GameObject* obj);
		void removeGameObject(GameObject* obj);

		void processEvents();

		inline std::size_t countObjects(){ return objects_.size(); }

	private:
		GameEventsManager(){}
		GameEventsManager(const GameEventsManager&) = delete;
		GameEventsManager& operator=(const GameEventsManager&) = delete;
		GameEventsManager(GameEventsManager&&) = delete;
		GameEventsManager& operator=(GameEventsManager&&) = delete;
		void collectDeleted();
		void processOutOfScreenEvents();
		void handleKeyEvents(sf::Keyboard::Key key);
		void handleCollisions();

	private:
		std::vector<GameObject*> objects_;
		std::shared_ptr<sf::RenderWindow> window_;
	};

} // tf

#endif // GAME_EVENTS_MANAGER_HPP