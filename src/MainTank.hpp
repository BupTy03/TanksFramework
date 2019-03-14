#pragma once
#ifndef MAIN_TANK_HPP
#define MAIN_TANK_HPP

#include "Tank.hpp"

#include <SFML/System/Vector2.hpp>

namespace tf
{
	struct MainTank : Tank
	{
		MainTank();
		MainTank(sf::Vector2f pos, float sz);
		MainTank(sf::Vector2f pos, float sz, float step);
		virtual ~MainTank();

		virtual void keyEvent(sf::Keyboard::Key which) override;
	};
}

#endif // MAIN_TANK_HPP