#include "ArmoredWall.hpp"

#include "Tank.hpp"
#include "Bullet.hpp"

#include <cassert>


namespace tf
{

	ArmoredWall::ArmoredWall(const sf::Vector2f& sz, const sf::Vector2f& pos)
		: Wall(sz, pos) 
	{
		setFillColor(sf::Color{100, 33, 33});
		setBorderColor(sf::Color{68, 21, 21});
	}

	void ArmoredWall::handleCollision(GameObject* obj)
	{
		if(obj->getType() == GameObject::GameObjectType::BULLET) {
			auto bullet = dynamic_cast<Bullet*>(obj);
			assert(bullet != nullptr && "bullet ptr was null");

			const sf::FloatRect bulletGeomentryRect(
				bullet->getPosition(),
				{bullet->getSize(), bullet->getSize()}
			);

			if(getRectShape().getGlobalBounds()
				.intersects(bulletGeomentryRect)) {
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
			
			if(getRectShape().getGlobalBounds().intersects(tankGeometryRect)) {
				tank->deleteLater();
			}
		}
	}

}
