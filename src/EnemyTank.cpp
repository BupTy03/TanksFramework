#include "EnemyTank.hpp"

#include <random>
#include <ctime>


namespace tf
{
	EnemyTank::EnemyTank(float step, float sz, const sf::Vector2f& pos)
		: Tank(step, sz, pos)
		, moveTimer_{}
		, changeDirTimer_{}
		, shotTimer_{}
	{
		moveTimer_.onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeStep);
		changeDirTimer_.onTimerCall.connect(this, &EnemyTank::changeDir);
		shotTimer_.onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeShot);
		moveTimer_.start(1000);
		changeDirTimer_.start(4000);
		shotTimer_.start(2000);
		srand(time(nullptr));
		this->setFillColor(sf::Color{220, 20, 60});
		this->setBorderColor(sf::Color{140, 0, 32});
	}

	void EnemyTank::changeDir() { setDirection(static_cast<Direction>(rand() % 4)); }

}
