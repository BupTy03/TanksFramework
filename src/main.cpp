#include "Game.hpp"
#include "Wall.hpp"
#include "ArmoredWall.hpp"
#include "MainTank.hpp"
#include "EnemyTank.hpp"

#include <SFML/Graphics.hpp>

#include <memory>


int main()
{
	constexpr unsigned int window_width = 800u;
	constexpr unsigned int width_in_cells = 20u;

	tf::Game game{"Tanks 2.0", window_width, width_in_cells};

	for(unsigned int i = 0u; i < width_in_cells; ++i) {
		for(unsigned int j = 0u; j < width_in_cells; ++j) {
			if(i == 0u || j == 0u || i == width_in_cells - 1u || j == width_in_cells - 1u) {
				if((i == 0u && j == 0u) || (i == width_in_cells - 1u && j == width_in_cells - 1u) ||
					(i == 0u && j == width_in_cells - 1u) || (j == 0u && i == width_in_cells - 1u)) {
					game.place(new tf::ArmoredWall(), sf::Vector2u{i, j});
				}
				else {
					game.place(new tf::Wall(), sf::Vector2u{i, j});
				}
			}
		}
	}

	game.place(new tf::MainTank(), sf::Vector2u{3u, 3u});
	game.place(new tf::EnemyTank(), sf::Vector2u{6u, 14u});
	game.start();

	return 0;
}
