#include "Wall.hpp"
#include "Bullet.hpp"
#include "Tank.hpp"

#include <cassert>

namespace tf
{
	Wall::Wall(sf::Vector2f sz, sf::Vector2f pos)
		: GameObject(GameObjectType::WALL) 
		, rectShape_{new sf::RectangleShape{sz}}
	{
		rectShape_->setPosition(pos);
		rectShape_->setFillColor(sf::Color{107, 109, 99});
		rectShape_->setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		rectShape_->setOutlineColor(sf::Color{62, 64, 55});
	}

	void Wall::setSize(float sz)
	{
		rectShape_->setOutlineThickness(-sz / 9.f);
		rectShape_->setSize({sz, sz});
	}

	void Wall::handleCollision(GameObject* obj)
	{
		if(obj->getType() == GameObject::GameObjectType::BULLET) {
			auto bullet = dynamic_cast<Bullet*>(obj);
			assert(bullet != nullptr && "bullet ptr was null");

			const sf::FloatRect bulletGeomentryRect(
				bullet->getPosition(),
				{bullet->getSize(), bullet->getSize()}
			);

			if(rectShape_->getGlobalBounds()
				.intersects(bulletGeomentryRect)) {
				this->deleteLater();
				bullet->deleteLater();
			}
		}
		else if(obj->getType() == GameObject::GameObjectType::TANK) {
			auto tank = dynamic_cast<Tank*>(obj);
			assert(tank != nullptr && "tank ptr was null!");

			const auto size_of_tank = tank->getSize() * 3.f;
			const sf::FloatRect tankGeometryRect(
				tank->getPosition(),
				{size_of_tank, size_of_tank}
			);
			
			if(rectShape_->getGlobalBounds().intersects(tankGeometryRect)) {
				this->deleteLater();
				tank->deleteLater();
			}
		}
	}

}