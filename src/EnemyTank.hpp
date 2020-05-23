#pragma once

#include "Tank.hpp"


namespace tf
{

	class EnemyTank : public Tank
	{
	public:
		EnemyTank();

	private:
		virtual void changeDir();
	
	private:
		GameTimer moveTimer_;
		GameTimer changeDirTimer_;
		GameTimer shotTimer_;
	};

}
