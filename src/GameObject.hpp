#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "GameTimer.hpp"
#include "GameEventsManager.hpp"
#include "signal.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

namespace tf
{
	class GameEventsManager;

	struct GameObject
	{
		enum class GameObjectType {
			WALL, TANK, BULLET 
		};

		explicit GameObject(GameObjectType type);
		virtual ~GameObject();

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		GameObject(GameObject&& other) = delete;
		GameObject& operator=(GameObject& other) = delete;

		inline std::size_t getId(){ return id_; }

		void setGameEventsManager(GameEventsManager* manager);

		virtual void draw(sf::RenderWindow&) = 0;

		virtual float getSize() const = 0;
		virtual void setSize(float sz) = 0;

		virtual void setFillColor(const sf::Color& color) = 0;
		virtual sf::Color getFillColor() const = 0;

		virtual void setBorderColor(const sf::Color& color) = 0;
		virtual sf::Color getBorderColor() const = 0;

		virtual sf::Vector2f getPosition() const = 0;
		virtual void setPosition(sf::Vector2f pos) = 0;

		inline GameObjectType getType() const { return type_; }

		inline void deleteLater() { deleted_ = true; }
		inline bool isDeleted() const{ return deleted_; }

		virtual void keyEvent(sf::Keyboard::Key which){}
		virtual void outOfScreenEvent(const sf::RenderWindow& win){}

		virtual void handleCollision(GameObject*) {}

		my::signal<GameObject*> onDelete;

	protected:
		GameEventsManager* getGameEventsManager() { return manager_; }

	private:
		static std::size_t counter_;
		std::size_t id_{};
		const GameObjectType type_;
		GameEventsManager* manager_;
		bool deleted_{false};
	};

}

#endif // GAME_OBJECT_HPP