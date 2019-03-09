#ifndef GAME_HPP
#define GAME_HPP

#include "Wall.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <memory>

namespace tf
{

	struct Game
	{
		// sz(width and height) - number of cells to fit them in the map
		Game(std::shared_ptr<sf::RenderWindow> w, sf::Vector2u sz);
		virtual ~Game();

		virtual sf::Vector2u getSizeInWalls() const;
		void mainLoop();

		void addWall(Wall* w, sf::Vector2u coords);
		void delWall(Wall* w);

		virtual void drawAll();

	protected:		
		virtual void drawWalls();
		virtual bool computeLogic();

	private:
		std::shared_ptr<sf::RenderWindow> win_;
		sf::Vector2u szInCells_;
		std::vector<Wall*> walls_;
	};

}

#endif // GAME_HPP