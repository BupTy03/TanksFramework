#include "Game.hpp"
#include "Wall.hpp"
#include "Bullet.hpp"
#include "Tank.hpp"
#include "MainTank.hpp"
#include "EnemyTank.hpp"
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
	constexpr unsigned int cell_width = 20u;

	tf::Game game("Tanks 2.0", window_width, cell_width);
	// game.place(new tf::MainTank({40.f * 8.f, 40.f * 8.f}, 50.f, 50.f));
	// game.place(new tf::EnemyTank({0.f, 0.f}, 50.f, 50.f));
	game.place(new tf::MainTank, {0u, 0u});
	game.place(new tf::EnemyTank, {6u, 6u});
	game.start();

	return 0;
}