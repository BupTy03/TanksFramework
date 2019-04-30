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
		explicit MainTank();
		explicit MainTank(sf::Vector2f pos, float sz);
		explicit MainTank(sf::Vector2f pos, float sz, float step);
		virtual ~MainTank();

		virtual void outOfScreenEvent(const sf::RenderWindow& win) override;
		virtual void keyEvent(sf::Keyboard::Key which) override;

	protected:
		virtual void init();

	protected:
		GameTimer* moveTimer_{nullptr};
	};
}

#endif // MAIN_TANK_HPP