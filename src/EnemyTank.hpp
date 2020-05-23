#pragma once

#include "GameTimer.hpp"
#include "Tank.hpp"


namespace tf
{

	class EnemyTank : public Tank
	{
	public:
		EnemyTank();

	private:
		void changeDirection();
	
	private:
		GameTimer moveTimer_;
		GameTimer changeDirTimer_;
		GameTimer shotTimer_;
	};

}
