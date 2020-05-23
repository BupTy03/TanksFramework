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

		if(getDirection() == Direction::forward())
			setPosition(sf::Vector2f{curr_pos.x, win_sz.y - curr_sz});
		else if(getDirection() == Direction::backward())
			setPosition(sf::Vector2f{curr_pos.x, -2.f * curr_sz});
		else if(getDirection() == Direction::left())
			setPosition(sf::Vector2f{win_sz.x - curr_sz, curr_pos.y});
		else if(getDirection() == Direction::right())
			setPosition(sf::Vector2f{-2.f * curr_sz, curr_pos.y});

		turn(getDirection());
	}

	void MainTank::keyEvent(sf::Keyboard::Key which)
	{
		switch (which)
		{
		case sf::Keyboard::Key::W:
			setDirection(Direction::forward());
			break;
		case sf::Keyboard::Key::S:
			setDirection(Direction::backward());
			break;
		case sf::Keyboard::Key::A:
			setDirection(Direction::left());
			break;
		case sf::Keyboard::Key::D:
			setDirection(Direction::right());
			break;
		case sf::Keyboard::Key::Space:
			makeShot();
			break;
		default: 
			break;
		}
	}

}
