#include "Game.hpp"

#include <algorithm>

namespace tf
{

	Game::Game(std::shared_ptr<sf::RenderWindow> w, sf::Vector2u sz) 
		: win_{w}
		, szInCells_{sz}
	{
	}

	Game::~Game()
	{
		for(auto wall : walls_) {
			delete wall;
		}
	}

	sf::Vector2u Game::getSizeInWalls() const
	{
		auto sz = win_->getSize();
		return {sz.x / szInCells_.x, sz.y / szInCells_.y};
	}

	void Game::addWall(Wall* w, sf::Vector2u coords)
	{
		if(w == nullptr || 
			std::find(std::cbegin(walls_), std::cend(walls_), w) != std::cend(walls_)) {
			return;
		}
		sf::Vector2f new_sz;
		new_sz.x = static_cast<float>(win_->getSize().x / szInCells_.x);
		new_sz.y = static_cast<float>(win_->getSize().y / szInCells_.y);
		w->setSize(new_sz);
		w->setPosition({coords.x * new_sz.x, coords.y * new_sz.y});

		walls_.push_back(w);
	}

	void Game::delWall(Wall* w)
	{
		if(w == nullptr) {
			return;
		}

		walls_.erase(
			std::remove(std::begin(walls_), std::end(walls_), w), 
			std::end(walls_)
		);
	}

	void Game::drawWalls()
	{
		for(auto w_ptr : walls_) {
			w_ptr->draw(*win_);
		}
	}

	void Game::drawAll()
	{
		drawWalls();
	}

	bool Game::computeLogic()
	{
		return false;
	}

}