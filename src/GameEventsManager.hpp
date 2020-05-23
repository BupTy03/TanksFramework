#pragma once

#include "GameObject.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <vector>

namespace tf
{
	class GameObject;

	class GameEventsManager
	{
	public:
		GameEventsManager() = default;
		~GameEventsManager();

		GameEventsManager(const GameEventsManager&) = delete;
		GameEventsManager& operator=(const GameEventsManager&) = delete;
		GameEventsManager(GameEventsManager&&) = delete;
		GameEventsManager& operator=(GameEventsManager&&) = delete;

		void collectDeleted();
		void processOutOfScreenEvents(const sf::RenderWindow& window);
		void handleKeyEvents(sf::Keyboard::Key key);
		void handleCollisions();

		void addGameObject(GameObject* obj);
		void removeGameObject(GameObject* obj);

		void processEvents(sf::RenderWindow& window);

		std::size_t countObjects() const;
		const std::vector<GameObject*>& getObjects() const;

	private:
		std::vector<GameObject*> objects_;
	};

}
