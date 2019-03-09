#include "Game.hpp"
#include "Wall.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>

int main()
{
	constexpr int window_width = 800;
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode({ window_width, window_width }), "Tanks 2.0");

	tf::Game game(window, sf::Vector2u(20, 20));

	game.addWall(new tf::Wall(), {3, 3});
	game.addWall(new tf::Wall(), {4, 3});
	game.addWall(new tf::Wall(), {5, 3});
	game.addWall(new tf::Wall(), {6, 3});
	game.addWall(new tf::Wall(), {7, 3});

	game.addWall(new tf::Wall(), {4, 5});
	game.addWall(new tf::Wall(), {5, 5});
	game.addWall(new tf::Wall(), {6, 5});
	game.addWall(new tf::Wall(), {4, 6});
	game.addWall(new tf::Wall(), {5, 6});
	game.addWall(new tf::Wall(), {6, 6});
	game.addWall(new tf::Wall(), {4, 7});
	game.addWall(new tf::Wall(), {5, 7});
	game.addWall(new tf::Wall(), {6, 7});

	game.addWall(new tf::Wall(), {12, 3});
	game.addWall(new tf::Wall(), {13, 3});
	game.addWall(new tf::Wall(), {14, 3});
	game.addWall(new tf::Wall(), {15, 3});
	game.addWall(new tf::Wall(), {16, 3});

	game.addWall(new tf::Wall(), {13, 5});
	game.addWall(new tf::Wall(), {14, 5});
	game.addWall(new tf::Wall(), {15, 5});
	game.addWall(new tf::Wall(), {13, 6});
	game.addWall(new tf::Wall(), {14, 6});
	game.addWall(new tf::Wall(), {15, 6});
	game.addWall(new tf::Wall(), {13, 7});
	game.addWall(new tf::Wall(), {14, 7});
	game.addWall(new tf::Wall(), {15, 7});

	game.addWall(new tf::Wall(), {9, 10});
	game.addWall(new tf::Wall(), {10, 10});
	game.addWall(new tf::Wall(), {9, 11});
	game.addWall(new tf::Wall(), {10, 11});


	game.addWall(new tf::Wall(), {2, 13});
	game.addWall(new tf::Wall(), {3, 14});
	game.addWall(new tf::Wall(), {4, 15});
	game.addWall(new tf::Wall(), {5, 16});

	game.addWall(new tf::Wall(), {5, 16});
	game.addWall(new tf::Wall(), {6, 16});
	game.addWall(new tf::Wall(), {7, 16});
	game.addWall(new tf::Wall(), {8, 16});
	game.addWall(new tf::Wall(), {9, 16});
	game.addWall(new tf::Wall(), {10, 16});
	game.addWall(new tf::Wall(), {11, 16});
	game.addWall(new tf::Wall(), {12, 16});
	game.addWall(new tf::Wall(), {13, 16});

	game.addWall(new tf::Wall(), {17, 13});
	game.addWall(new tf::Wall(), {16, 14});
	game.addWall(new tf::Wall(), {15, 15});
	game.addWall(new tf::Wall(), {14, 16});

	game.drawAll();
	
	window->display();

	sf::sleep(sf::seconds(20));

	return 0;
}