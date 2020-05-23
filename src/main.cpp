#include "Game.hpp"
#include "Wall.hpp"
#include "ArmoredWall.hpp"
#include "MainTank.hpp"
#include "EnemyTank.hpp"

#include <SFML/Graphics.hpp>


int main()
{
	constexpr auto window_width = 800;
	constexpr auto width_in_cells = 20;

	tf::Game game{"Tanks 2.0", window_width, width_in_cells};

	for(unsigned int i = 0; i < width_in_cells; ++i) {
		for(unsigned int j = 0; j < width_in_cells; ++j) {
			if(i == 0 || j == 0 || i == width_in_cells - 1 || j == width_in_cells - 1) {
				if((i == 0 && j == 0) || (i == width_in_cells - 1 && j == width_in_cells - 1) ||
					(i == 0 && j == width_in_cells - 1) || (j == 0 && i == width_in_cells - 1)) {
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
