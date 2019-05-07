#ifndef ARMORED_WALL
#define ARMORED_WALL

#include "Wall.hpp"

namespace tf
{
	struct ArmoredWall : Wall
	{
		explicit ArmoredWall(sf::Vector2f sz = {0.f, 0.f}, sf::Vector2f pos = {0.f, 0.f});
		virtual ~ArmoredWall(){}

		virtual void handleCollision(GameObject* obj) override;
	};
}

#endif