#include "Wall.hpp"
#include "Bullet.hpp"
#include "Tank.hpp"

#include <cassert>


namespace tf
{
	Wall::Wall(const sf::Vector2f& sz, const sf::Vector2f& pos)
		: GameObject(GameObjectType::WALL) 
		, rectShape_{sz}
	{
		rectShape_.setPosition(pos);
		rectShape_.setFillColor(sf::Color{107, 109, 99});
		rectShape_.setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		rectShape_.setOutlineColor(sf::Color{62, 64, 55});
	}

	float Wall::getSize() const 
	{ 
		return rectShape_.getSize().x;
	}

	void Wall::setSize(float sz)
	{
		rectShape_.setOutlineThickness(-sz / 9.f);
		rectShape_.setSize(sf::Vector2f{sz, sz});
	}

	sf::Vector2f Wall::getPosition() const 
	{ 
		return rectShape_.getPosition(); 
	}

	void Wall::setPosition(const sf::Vector2f& pos) 
	{ 
		rectShape_.setPosition(pos); 
	}

	void Wall::draw(sf::RenderWindow& win) 
	{ 
		win.draw(rectShape_); 
	}

	void Wall::setFillColor(const sf::Color& color) 
	{ 
		rectShape_.setFillColor(color); 
	}

	sf::Color Wall::getFillColor() const 
	{ 
		return rectShape_.getFillColor();
	}

	void Wall::setBorderColor(const sf::Color& color) 
	{ 
		rectShape_.setOutlineColor(color); 
	}

	sf::Color Wall::getBorderColor() const 
	{ 
		return rectShape_.getOutlineColor(); 
	}

	void Wall::handleCollision(GameObject* obj)
	{
		if(obj->getType() == GameObject::GameObjectType::BULLET) {
			auto bullet = dynamic_cast<Bullet*>(obj);
			assert(bullet != nullptr && "bullet ptr was null");

			const sf::FloatRect bulletGeomentryRect{
				bullet->getPosition(),
				{bullet->getSize(), bullet->getSize()}
			};

			if(rectShape_.getGlobalBounds()
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
				sf::Vector2f{size_of_tank, size_of_tank}
			);
			
			if(rectShape_.getGlobalBounds().intersects(tankGeometryRect)) {
				this->deleteLater();
				tank->deleteLater();
			}
		}
	}

	const sf::RectangleShape& Wall::getRectShape() const 
	{ 
		return rectShape_;
	}

}
