#pragma once

#include "GameObject.hpp"
#include "MovingGameObject.hpp"
#include "GameEventsManager.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>


namespace tf
{

	class Game
	{
	public:
		// sz(width and height) - number of cells to fit them in the map
		explicit Game(
			const std::string& name, 
			unsigned int size_in_pixels, 
			unsigned int count_cells
		);

		virtual unsigned getSizeInBlocks() const;
		void start();
		bool place(GameObject* obj, const sf::Vector2u& coordinates);

	private:
		bool checkBounds(const sf::Vector2u& coordinates);
		void drawAll(sf::RenderWindow& win);

	private:
		sf::RenderWindow win_;
		GameEventsManager manager_;
		const unsigned int countCells_;
	};

}
