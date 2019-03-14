#include "Game.hpp"
#include "Wall.hpp"
#include "Bullet.hpp"
#include "Tank.hpp"
#include "GameTimer.hpp"
#include "GameEventsManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>
#include <iostream>

void notify()
{
	std::cout << "Bullet deleted!\n";
}

int main()
{
	constexpr unsigned int window_width = 800u;
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_width, window_width), "Tanks 2.0");

	tf::Game game(window, {20u, 20u});
	(tf::GameEventsManager::Instance()).setWindowSize({
		static_cast<float>(window->getSize().x), 
		static_cast<float>(window->getSize().y)
	});

	auto bl = new tf::Bullet({400.f - 5.f, 400.f - 5.f}, 10.f, 50.f);
	bl->onDelete.connect(notify);
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		window->clear();
		if((tf::GameEventsManager::Instance()).countObjects() > 0){
			bl->draw(*window);
		}
		window->display();
		(tf::GameEventsManager::Instance()).processEvents();
		(tf::GameTimersDispatcher::Instance()).dispatch();
	}

	return 0;
}