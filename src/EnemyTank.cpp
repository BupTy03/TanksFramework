#include "EnemyTank.hpp"

#include <random>
#include <ctime>


namespace tf
{
	EnemyTank::EnemyTank()
		: Tank()
		, moveTimer_()
		, changeDirTimer_()
		, shotTimer_()
	{
		moveTimer_.onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeStep);
		changeDirTimer_.onTimerCall.connect(this, &EnemyTank::changeDir);
		shotTimer_.onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeShot);
		moveTimer_.start(1000);
		changeDirTimer_.start(4000);
		shotTimer_.start(2000);

		setFillColor(sf::Color{220, 20, 60});
		setBorderColor(sf::Color{140, 0, 32});

		static const bool rand_initialized = [] { srand(time(nullptr)); return true; }();
	}

	void EnemyTank::changeDir() { setDirection(static_cast<Direction>(rand() % 4)); }

}
