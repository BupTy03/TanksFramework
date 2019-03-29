#pragma once
#ifndef MAIN_TANK_HPP
#define MAIN_TANK_HPP

#include "GameTimer.hpp"
#include "Tank.hpp"

#include <SFML/System/Vector2.hpp>

namespace tf
{
	struct MainTank : Tank
	{
		MainTank(std::shared_ptr<sf::RenderWindow> w);
		MainTank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz);
		MainTank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz, float step);
		virtual ~MainTank() { delete moveTimer_; }

		virtual void outOfScreenEvent() override;
		virtual void keyEvent(sf::Keyboard::Key which) override;

	private:
		GameTimer* moveTimer_{nullptr};
	};
}

#endif // MAIN_TANK_HPP