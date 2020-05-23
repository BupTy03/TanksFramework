#pragma once

#include "Wall.hpp"


namespace tf
{
	class ArmoredWall : public Wall
	{
	public:
		explicit ArmoredWall(
			const sf::Vector2f& sz = {0.f, 0.f}, 
			const sf::Vector2f& pos = {0.f, 0.f}
		);

		void handleCollision(GameObject* obj) override;
	};
}
