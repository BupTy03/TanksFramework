#pragma once

#include "Tank.hpp"


namespace tf
{

	class EnemyTank : public Tank
	{
	public:
		explicit EnemyTank(
			float step = 0.f, 
			float sz = 0.f, 
			const sf::Vector2f& pos = {0.f, 0.f}
		);

	private:
		virtual void changeDir();
	
	private:
		GameTimer moveTimer_;
		GameTimer changeDirTimer_;
		GameTimer shotTimer_;
	};

}
