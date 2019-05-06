#include "Game.hpp"

#define DEBUG

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cassert>

namespace tf
{

	Game::Game(const std::string& name, unsigned int size_in_pixels, unsigned int count_cells) 
		: win_{new sf::RenderWindow(sf::VideoMode(size_in_pixels, size_in_pixels), name)}
		, manager_{new GameEventsManager}
		, countCells_{count_cells} {}

	Game::~Game()
	{ 
		delete win_;
		delete manager_; 
	}

	void Game::drawAll(sf::RenderWindow& win)
	{
		for(auto obj : manager_->getObjects()) {
			obj->draw(win);
		}
	}

	void Game::start()
	{
		while (win_->isOpen()) {
			(tf::GameTimersDispatcher::Instance()).dispatch();
			manager_->processEvents(*win_);
			win_->clear();
			if(manager_->countObjects() <= 0) {
				win_->close();
				return;
			}
			drawAll(*win_);
			win_->display();
		}
	}

	bool Game::place(MovingGameObject* obj, sf::Vector2u coordinates)
	{
		assert(obj != nullptr && "obj was nullptr");
		if(!checkBounds(coordinates)){
			return false;
		}
		const auto new_size = static_cast<float>(win_->getSize().x / countCells_);
		obj->setPosition({coordinates.x * new_size, coordinates.y * new_size});
		obj->setSize(new_size);
		if(obj->getStep() <= 0.f) {
			obj->setStep(obj->getSize());
		}
		obj->setGameEventsManager(manager_);
		manager_->addGameObject(obj);
		return true;
	}

}