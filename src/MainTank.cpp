#include "MainTank.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


namespace tf
{
	MainTank::MainTank()
		: Tank()
		, moveTimer_()
	{ 
		moveTimer_.onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeStep);
		moveTimer_.start(1000);
		setFillColor(sf::Color{23, 164, 113});
		setBorderColor(sf::Color{31, 87, 67});
	}

	void MainTank::outOfScreenEvent(const sf::RenderWindow& win)
	{
		const auto curr_pos = getPosition();
		const auto curr_sz = getSize();
		const auto win_sz = win.getSize();
		switch (getDirection()) {
			case Direction::FORWARD:
				setPosition(sf::Vector2f{curr_pos.x, win_sz.y - curr_sz});
				break;
			case Direction::BACKWARD:
				setPosition(sf::Vector2f{curr_pos.x, -2.f * curr_sz});
				break;
			case Direction::LEFT:
				setPosition(sf::Vector2f{win_sz.x - curr_sz, curr_pos.y});
				break;
			case Direction::RIGHT:
				setPosition(sf::Vector2f{-2.f * curr_sz, curr_pos.y});
				break;
			default: 
				break;
		}
		turn(getDirection());
	}

	void MainTank::keyEvent(sf::Keyboard::Key which)
	{
		switch (which)
		{
		case sf::Keyboard::Key::W:
			setDirection(Direction::FORWARD);
			break;
		case sf::Keyboard::Key::S:
			setDirection(Direction::BACKWARD);
			break;
		case sf::Keyboard::Key::A:
			setDirection(Direction::LEFT);
			break;
		case sf::Keyboard::Key::D:
			setDirection(Direction::RIGHT);
			break;
		case sf::Keyboard::Key::Space:
			makeShot();
			break;
		default: 
			break;
		}
	}

}
