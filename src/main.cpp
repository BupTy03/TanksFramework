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
	(tf::GameEventsManager::Instance()).setWindow(window);

	auto mtnk = new tf::MainTank(window, {40.f * 8.f, 40.f * 8.f}, 50.f, 50.f);
	while (window->isOpen()) {
		(tf::GameTimersDispatcher::Instance()).dispatch();
		(tf::GameEventsManager::Instance()).processEvents();
		window->clear();
		if((tf::GameEventsManager::Instance()).countObjects() > 0) {
			mtnk->draw();
		}
		window->display();
	}

	return 0;
}