#include "Game.hpp"
#include "Wall.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>

int main()
{
	constexpr unsigned int window_width = 800u;
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_width, window_width), "Tanks 2.0");

	tf::Game game(window, {20u, 20u});

	game.addWall(new tf::Wall(), {3u, 3u});
	game.addWall(new tf::Wall(), {4u, 3u});
	game.addWall(new tf::Wall(), {5u, 3u});
	game.addWall(new tf::Wall(), {6u, 3u});
	game.addWall(new tf::Wall(), {7u, 3u});

	game.addWall(new tf::Wall(), {4u, 5u});
	game.addWall(new tf::Wall(), {5u, 5u});
	game.addWall(new tf::Wall(), {6u, 5u});
	game.addWall(new tf::Wall(), {4u, 6u});
	game.addWall(new tf::Wall(), {5u, 6u});
	game.addWall(new tf::Wall(), {6u, 6u});
	game.addWall(new tf::Wall(), {4u, 7u});
	game.addWall(new tf::Wall(), {5u, 7u});
	game.addWall(new tf::Wall(), {6u, 7u});

	game.addWall(new tf::Wall(), {12u, 3u});
	game.addWall(new tf::Wall(), {13u, 3u});
	game.addWall(new tf::Wall(), {14u, 3u});
	game.addWall(new tf::Wall(), {15u, 3u});
	game.addWall(new tf::Wall(), {16u, 3u});

	game.addWall(new tf::Wall(), {13u, 5u});
	game.addWall(new tf::Wall(), {14u, 5u});
	game.addWall(new tf::Wall(), {15u, 5u});
	game.addWall(new tf::Wall(), {13u, 6u});
	game.addWall(new tf::Wall(), {14u, 6u});
	game.addWall(new tf::Wall(), {15u, 6u});
	game.addWall(new tf::Wall(), {13u, 7u});
	game.addWall(new tf::Wall(), {14u, 7u});
	game.addWall(new tf::Wall(), {15u, 7u});

	game.addWall(new tf::Wall(), {9u, 10u});
	game.addWall(new tf::Wall(), {10u, 10u});
	game.addWall(new tf::Wall(), {9u, 11u});
	game.addWall(new tf::Wall(), {10u, 11u});


	game.addWall(new tf::Wall(), {2u, 13u});
	game.addWall(new tf::Wall(), {3u, 14u});
	game.addWall(new tf::Wall(), {4u, 15u});
	game.addWall(new tf::Wall(), {5u, 16u});

	game.addWall(new tf::Wall(), {5u, 16u});
	game.addWall(new tf::Wall(), {6u, 16u});
	game.addWall(new tf::Wall(), {7u, 16u});
	game.addWall(new tf::Wall(), {8u, 16u});
	game.addWall(new tf::Wall(), {9u, 16u});
	game.addWall(new tf::Wall(), {10u, 16u});
	game.addWall(new tf::Wall(), {11u, 16u});
	game.addWall(new tf::Wall(), {12u, 16u});
	game.addWall(new tf::Wall(), {13u, 16u});

	game.addWall(new tf::Wall(), {17u, 13u});
	game.addWall(new tf::Wall(), {16u, 14u});
	game.addWall(new tf::Wall(), {15u, 15u});
	game.addWall(new tf::Wall(), {14u, 16u});

	game.drawAll();
	
	window->display();

	sf::sleep(sf::seconds(10.f));

	return 0;
}