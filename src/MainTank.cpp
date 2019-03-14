#include "MainTank.hpp"

namespace tf
{
	MainTank::MainTank()
		: Tank()
	{

	}
	MainTank::MainTank(sf::Vector2f pos, float sz)
		: Tank(pos, sz)
	{

	}
	MainTank::MainTank(sf::Vector2f pos, float sz, float step)
		: Tank(pos, sz, step)
	{

	}
	MainTank::~MainTank()
	{
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