#include "MainTank.hpp"

namespace tf
{
	MainTank::MainTank(std::shared_ptr<sf::RenderWindow> w)
		: Tank(std::move(w))
		, moveTimer_{new GameTimer()}
	{
		moveTimer_->onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeStep);
		moveTimer_->start(1000);
	}
	MainTank::MainTank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz)
		: Tank(std::move(w), pos, sz)
		, moveTimer_{new GameTimer()}
	{
		moveTimer_->onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeStep);
		moveTimer_->start(1000);
	}
	MainTank::MainTank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz, float step)
		: Tank(std::move(w), pos, sz, step)
		, moveTimer_{new GameTimer()}
	{
		moveTimer_->onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeStep);
		moveTimer_->start(1000);
	}
	MainTank::~MainTank()
	{
		delete moveTimer_;
	}

	void MainTank::outOfScreenEvent()
	{
		const auto curr_pos = getPosition();
		const auto curr_sz = getSize();
		const auto win_sz = win_->getSize();
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
		}
	}
}