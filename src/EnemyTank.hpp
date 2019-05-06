#pragma once
#ifndef ENEMY_TANK_HPP
#define ENEMY_TANK_HPP

#include "Tank.hpp"

namespace tf
{

	struct EnemyTank : Tank
	{
		explicit EnemyTank(float step = 0.f, float sz = 0.f, sf::Vector2f pos = {0.f, 0.f});
		virtual ~EnemyTank();

	protected:
		virtual void changeDir();
	
	protected:
		GameTimer* moveTimer_{nullptr};
		GameTimer* changeDirTimer_{nullptr};
		GameTimer* shotTimer_{nullptr};
	};

}

#endif // ENEMY_TANK_HPP