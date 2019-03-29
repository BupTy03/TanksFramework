#include "EnemyTank.hpp"

#include <random>
#include <ctime>

namespace tf
{

	EnemyTank::EnemyTank(std::shared_ptr<sf::RenderWindow> w)
		: Tank(std::move(w))
		, moveTimer_{new GameTimer()}
		, changeDirTimer_{new GameTimer()}
		, shotTimer_{new GameTimer()}
	{ init(); }

	EnemyTank::EnemyTank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz)
		: Tank(std::move(w), pos, sz)
		, moveTimer_{new GameTimer()}
		, changeDirTimer_{new GameTimer()}
		, shotTimer_{new GameTimer()}
	{ init(); }

	EnemyTank::EnemyTank(std::shared_ptr<sf::RenderWindow> w, sf::Vector2f pos, float sz, float step)
		: Tank(std::move(w), pos, sz, step)
		, moveTimer_{new GameTimer()}
		, changeDirTimer_{new GameTimer()}
		, shotTimer_{new GameTimer()}
	{ init(); }

	EnemyTank::~EnemyTank() 
	{ 
		delete moveTimer_; 
		delete changeDirTimer_; 
		delete shotTimer_;
	}

	void EnemyTank::init()
	{
		moveTimer_->onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeStep);
		changeDirTimer_->onTimerCall.connect(this, &EnemyTank::changeDir);
		shotTimer_->onTimerCall.connect(dynamic_cast<Tank*>(this), &Tank::makeShot);
		moveTimer_->start(1000);
		changeDirTimer_->start(4000);
		shotTimer_->start(2000);
		srand(time(nullptr));
		this->setFillColor(sf::Color(220, 20, 60));
		this->setBorderColor(sf::Color(140, 0, 32));
	}

	void EnemyTank::changeDir(){ this->setDirection(static_cast<Direction>(rand() % 4)); }

}