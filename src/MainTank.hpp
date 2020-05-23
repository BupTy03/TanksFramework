#pragma once

#include "GameTimer.hpp"
#include "Tank.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>


class RenderWindow;

namespace tf
{
	class MainTank : public Tank
	{
	public:
		MainTank();

		void outOfScreenEvent(const sf::RenderWindow& win) override;
		void keyEvent(sf::Keyboard::Key which) override;

	private:
		GameTimer moveTimer_;
	};
}
