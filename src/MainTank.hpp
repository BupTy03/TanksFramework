#ifndef MAIN_TANK_HPP
#define MAIN_TANK_HPP

#include "GameTimer.hpp"
#include "Tank.hpp"

#include <SFML/System/Vector2.hpp>

namespace tf
{
	struct MainTank : Tank
	{
		explicit MainTank(float step = 0.f, float sz = 0.f, sf::Vector2f pos = {0.f, 0.f});
		virtual ~MainTank();

		virtual void outOfScreenEvent(const sf::RenderWindow& win) override;
		virtual void keyEvent(sf::Keyboard::Key which) override;

	protected:
		GameTimer* moveTimer_{nullptr};
	};
}

#endif // MAIN_TANK_HPP