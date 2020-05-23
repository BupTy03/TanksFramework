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
		explicit MainTank(
			float step = 0.f, 
			float sz = 0.f, 
			const sf::Vector2f& pos = sf::Vector2f{0.f, 0.f}
		);

		void outOfScreenEvent(const sf::RenderWindow& win) override;
		void keyEvent(sf::Keyboard::Key which) override;

	private:
		GameTimer moveTimer_;
	};
}
