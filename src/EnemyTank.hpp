#pragma once
#ifndef ENEMY_TANK_HPP
#define ENEMY_TANK_HPP

#include "Tank.hpp"

namespace tf
{

	struct EnemyTank : Tank
	{
		EnemyTank(std::shared_ptr<sf::RenderWindow> w);
		EnemyTank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz);
		EnemyTank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz, float step);
		virtual ~EnemyTank();

	protected:
		virtual void changeDir();
		virtual void init();
	
	protected:
		GameTimer* moveTimer_{nullptr};
		GameTimer* changeDirTimer_{nullptr};
		GameTimer* shotTimer_{nullptr};
	};

}

#endif // ENEMY_TANK_HPP