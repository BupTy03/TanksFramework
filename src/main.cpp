#include "Game.hpp"
#include "Wall.hpp"
#include "Bullet.hpp"
#include "Tank.hpp"
#include "GameTimer.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>

int main()
{
	constexpr unsigned int window_width = 800u;
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_width, window_width), "Tanks 2.0");

	tf::Game game(window, {20u, 20u});

	tf::Tank tnk({400.f - 100.f, 400.f - 100.f}, {50.f, 50.f}, {0.f, -10.f});
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		window->clear();
		tnk.draw(*window);
		window->display();
		(tf::GameTimersDispatcher::Instance()).dispatch();
	}

	return 0;
}