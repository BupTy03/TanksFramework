#pragma once
#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "GameTimer.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace tf
{

	struct GameObject
	{
		GameObject();
		virtual ~GameObject();

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		GameObject(GameObject&& other) = delete;
		GameObject& operator=(GameObject& other) = delete;

		std::size_t getId();

		virtual void draw(sf::RenderWindow& w) = 0;

		virtual sf::Vector2f getSize() const = 0;
		virtual void setSize(sf::Vector2f sz) = 0;

		virtual sf::Vector2f getPosition() const = 0;
		virtual void setPosition(sf::Vector2f pos) = 0;

		virtual const sf::IntRect& getRect() const = 0;

	private:
		static std::size_t counter_;
		std::size_t id_{};
	};

}

#endif // GAME_OBJECT_HPP