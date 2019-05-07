#ifndef GAME_HPP
#define GAME_HPP

#include "GameObject.hpp"
#include "MovingGameObject.hpp"
#include "GameEventsManager.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <memory>

namespace tf
{

	struct Game
	{
		// sz(width and height) - number of cells to fit them in the map
		explicit Game(const std::string& name, unsigned int size_in_pixels, unsigned int count_cells);
		virtual ~Game();

		virtual unsigned getSizeInBlocks() const { return win_->getSize().x / countCells_; }
		void start();
		bool place(GameObject* obj, sf::Vector2u coordinates);

	private:
		inline bool checkBounds(sf::Vector2u coordinates) { return coordinates.x < countCells_ && coordinates.y < countCells_; }
		void drawAll(sf::RenderWindow& win);

	private:
		sf::RenderWindow* win_;
		GameEventsManager* manager_;
		const unsigned int countCells_;
	};

}

#endif // GAME_HPP