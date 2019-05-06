#include "MainTank.hpp"

#include <iostream>
#include <chrono>

namespace tf
{
	MainTank::MainTank(float step, float sz, sf::Vector2f pos)
		: Tank(step, sz, pos)
		, moveTimer_{new GameTimer}
	{ 
		moveTimer_->onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeStep);
		moveTimer_->start(1000);
		setFillColor(sf::Color(23, 164, 113));
		setBorderColor(sf::Color(31, 87, 67));
	}

	MainTank::~MainTank() { delete moveTimer_; }

	void MainTank::outOfScreenEvent(const sf::RenderWindow& win)
	{
		const auto curr_pos = getPosition();
		const auto curr_sz = getSize();
		const auto win_sz = win.getSize();
		switch (getDirection()) {
			case Direction::FORWARD:
				setPosition({curr_pos.x, win_sz.y - curr_sz});
				break;
			case Direction::BACKWARD:
				setPosition({curr_pos.x, -2.f * curr_sz});
				break;
			case Direction::LEFT:
				setPosition({win_sz.x - curr_sz, curr_pos.y});
				break;
			case Direction::RIGHT:
				setPosition({-2.f * curr_sz, curr_pos.y});
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
		}
	}

}