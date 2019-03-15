#include "Game.hpp"
#include "Wall.hpp"
#include "Bullet.hpp"
#include "Tank.hpp"
#include "MainTank.hpp"
#include "GameTimer.hpp"
#include "GameEventsManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <memory>
#include <iostream>


int main()
{
	constexpr unsigned int window_width = 800u;
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_width, window_width), "Tanks 2.0");

	tf::Game game(window, {20u, 20u});
	(tf::GameEventsManager::Instance()).setWindowSize({
		static_cast<float>(window->getSize().x), 
		static_cast<float>(window->getSize().y)
	});

	auto mtnk = new tf::MainTank(window, {40.f * 8.f, 40.f * 8.f}, 50.f, 50.f);
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		window->clear();
		if((tf::GameEventsManager::Instance()).countObjects() > 0) {
			mtnk->draw();
		}
		window->display();
		(tf::GameEventsManager::Instance()).processEvents();
		(tf::GameTimersDispatcher::Instance()).dispatch();
	}

	return 0;
}