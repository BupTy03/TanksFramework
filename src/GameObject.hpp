#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "GameTimer.hpp"
#include "signal.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>

namespace tf
{

	struct GameObject
	{
		GameObject(std::shared_ptr<sf::RenderWindow> w);
		virtual ~GameObject();

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		GameObject(GameObject&& other) = delete;
		GameObject& operator=(GameObject& other) = delete;

		std::size_t getId();

		virtual void draw() = 0;

		virtual float getSize() const = 0;
		virtual void setSize(float sz) = 0;

		virtual sf::Vector2f getPosition() const = 0;
		virtual void setPosition(sf::Vector2f pos) = 0;

		void deleteLater();
		bool isDeleted() const;

		virtual void keyEvent(sf::Keyboard::Key which);
		virtual void outOfScreenEvent();

		my::signal<> onDelete;

	protected:
		std::shared_ptr<sf::RenderWindow> win_;
	private:
		static std::size_t counter_;
		std::size_t id_{};
		bool deleted_{false};
	};

}

#endif // GAME_OBJECT_HPP