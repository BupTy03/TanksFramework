#include "Game.hpp"

#include <cassert>


namespace tf
{

	Game::Game(const std::string& name, unsigned int size_in_pixels, unsigned int count_cells) 
		: win_{sf::VideoMode(size_in_pixels, size_in_pixels), name}
		, manager_{}
		, countCells_{count_cells} 
	{}

	void Game::drawAll(sf::RenderWindow& win)
	{
		for(auto obj : manager_.getObjects())
			obj->draw(win);
	}

	unsigned Game::getSizeInBlocks() const
	{
		return win_.getSize().x / countCells_;
	}

	bool Game::checkBounds(const sf::Vector2u& coordinates) 
	{ 
		return coordinates.x < countCells_ && coordinates.y < countCells_;
	}

	void Game::start()
	{
		while (win_.isOpen()) {
			(tf::GameTimersDispatcher::Instance()).dispatch();
			manager_.processEvents(win_);
			win_.clear();
			if(manager_.countObjects() <= 0) {
				win_.close();
				return;
			}
			drawAll(win_);
			win_.display();
		}
	}

	bool Game::place(GameObject* obj, const sf::Vector2u& coordinates)
	{
		assert(obj != nullptr);
		if(!checkBounds(coordinates)){
			return false;
		}
		const auto new_size = static_cast<float>(win_.getSize().x / countCells_);
		obj->setPosition({coordinates.x * new_size, coordinates.y * new_size});
		obj->setSize(new_size);

		auto movingGameObject = dynamic_cast<MovingGameObject*>(obj);
		if(movingGameObject != nullptr && movingGameObject->getStep() <= 0.f) {
			movingGameObject->setStep(movingGameObject->getSize());
		}
		obj->setGameEventsManager(&manager_);
		manager_.addGameObject(obj);
		return true;
	}

}
