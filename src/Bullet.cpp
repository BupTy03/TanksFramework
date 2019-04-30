#include "Bullet.hpp"
#include "Wall.hpp"

#define DEBUG
#include <cassert>

namespace tf
{

	Bullet::Bullet()
		: MovingGameObject(GameObjectType::BULLET)
		, moveTimer_(new GameTimer)
	{
		rectShape_.setFillColor(sf::Color(220, 20, 60));
		rectShape_.setOutlineColor(sf::Color(144, 0, 32));
		moveTimer_->onTimerCall.connect(this, &Bullet::makeStep);
		moveTimer_->start(100);
	}
	Bullet::Bullet(sf::Vector2f pos, float sz) 
		: MovingGameObject(GameObjectType::BULLET)
		, rectShape_{{sz, sz}}
		, moveTimer_(new GameTimer)
	{
		rectShape_.setPosition(pos);
		rectShape_.setOutlineThickness(-sz / 9.f);
		rectShape_.setFillColor(sf::Color(220, 20, 60));
		rectShape_.setOutlineColor(sf::Color(144, 0, 32));
		moveTimer_->onTimerCall.connect(this, &Bullet::makeStep);
		moveTimer_->start(100);
	}
	Bullet::Bullet(sf::Vector2f pos, float sz, float step)
		: MovingGameObject(GameObjectType::BULLET, step)
		, rectShape_{{sz, sz}}
		, moveTimer_(new GameTimer)
	{
		rectShape_.setPosition(pos);
		rectShape_.setOutlineThickness(-sz / 9.f);
		rectShape_.setFillColor(sf::Color(220, 20, 60));
		rectShape_.setOutlineColor(sf::Color(144, 0, 32));
		moveTimer_->onTimerCall.connect(this, &Bullet::makeStep);
		moveTimer_->start(100);
	}

	void Bullet::makeStep()
	{
		const auto ps = getPosition();
		const auto step = getStep();
		switch (getDirection())
		{
			case Direction::FORWARD:
				setPosition({ps.x, ps.y - step});
				break;
			case Direction::BACKWARD:
				setPosition({ps.x, ps.y + step});
				break;
			case Direction::LEFT:
				setPosition({ps.x - step, ps.y});
				break;
			case Direction::RIGHT:
				setPosition({ps.x + step, ps.y});
				break;
		}
	}

	void Bullet::setSize(float sz)
	{
		rectShape_.setOutlineThickness(-sz / 9.f);
		rectShape_.setSize({sz, sz});
	}

	void Bullet::handleCollision(GameObject* obj)
	{
		assert(obj != nullptr && "obj ptr was null");
		if(obj->getType() != GameObjectType::WALL) {
			return;
		}
		
		auto wall = dynamic_cast<Wall*>(obj);
		assert(wall != nullptr && "wall ptr was null");

		const sf::FloatRect wallGeometryRect(
			wall->getPosition(),
			{wall->getSize(), wall->getSize()}
		);
		if(this->rectShape_.getGlobalBounds()
			.intersects(wallGeometryRect)) {
				this->deleteLater();
				wall->deleteLater();
				return;
			}
	}

}