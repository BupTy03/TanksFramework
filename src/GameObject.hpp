#pragma once

#include "signal.hpp"
#include "GameTimer.hpp"
#include "GameEventsManager.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace tf
{
	class GameEventsManager;

	class GameObject
	{
	public:
		enum class GameObjectType {
			WALL, TANK, BULLET 
		};

		explicit GameObject(GameObjectType type);
		virtual ~GameObject();

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		GameObject(GameObject&& other) = delete;
		GameObject& operator=(GameObject& other) = delete;

		std::size_t getId() const;

		void setGameEventsManager(GameEventsManager* manager);

		virtual void draw(sf::RenderWindow&) = 0;

		virtual float getSize() const = 0;
		virtual void setSize(float sz) = 0;

		virtual void setFillColor(const sf::Color& color) = 0;
		virtual sf::Color getFillColor() const = 0;

		virtual void setBorderColor(const sf::Color& color) = 0;
		virtual sf::Color getBorderColor() const = 0;

		virtual sf::Vector2f getPosition() const = 0;
		virtual void setPosition(const sf::Vector2f& pos) = 0;

		GameObjectType getType() const;

		void deleteLater();
		bool isDeleted() const;

		virtual void keyEvent(sf::Keyboard::Key which) {}
		virtual void outOfScreenEvent(const sf::RenderWindow& win) {}

		virtual void handleCollision(GameObject*) {}

		my::signal<GameObject*> onDelete;

	protected:
		GameEventsManager* getGameEventsManager() const;

	private:
		static std::size_t counter_;

		std::size_t id_;
		const GameObjectType type_;
		GameEventsManager* manager_;
		bool deleted_;
	};

}
