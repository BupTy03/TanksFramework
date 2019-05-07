#include "Tank.hpp"
#include "Wall.hpp"

#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <cassert>

namespace tf
{

	Tank::Tank(float step, float sz, sf::Vector2f pos)
		: MovingGameObject(GameObjectType::TANK, step) 
	{
		for(auto& segment : body_) {
			segment = new sf::RectangleShape({sz, sz});
			segment->setFillColor(sf::Color(23, 164, 113));
			segment->setOutlineColor(sf::Color(31, 87, 67));
			segment->setOutlineThickness(-sz / 9.f);
		}

		setPosition(pos);
		turn(getDirection());
	}

	Tank::~Tank() 
	{ 
		for(auto sh : body_) { 
			delete sh; 
		}
	}

	void Tank::draw(sf::RenderWindow& win)
	{
		for(auto sh : body_) {
			win.draw(*sh);
		}
		for(auto bullet : bullets_) {
			bullet->draw(win);
		}
	}

	void Tank::setSize(float sz)
	{
		for(auto sh : body_) {
			sh->setSize({sz, sz});
			sh->setOutlineThickness(-sz / 9.f);
		}
		turn(getDirection());
	}

	void Tank::turn(Direction dir)
	{
		const auto sz = getSize();
		switch (dir) {
		case Direction::FORWARD:
			body_[0]->setPosition({currPos_.x + sz, currPos_.y});
			body_[1]->setPosition({currPos_.x, currPos_.y + sz});
			body_[2]->setPosition({currPos_.x + sz, currPos_.y + sz});
			body_[3]->setPosition({currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[4]->setPosition({currPos_.x, currPos_.y + 2.f * sz});
			body_[5]->setPosition({currPos_.x + 2.f * sz, currPos_.y + 2.f * sz});
			break;
		case Direction::BACKWARD:
			body_[0]->setPosition({currPos_.x, currPos_.y});
			body_[1]->setPosition({currPos_.x + 2.f * sz, currPos_.y});
			body_[2]->setPosition({currPos_.x, currPos_.y + sz});
			body_[3]->setPosition({currPos_.x + sz, currPos_.y + sz});
			body_[4]->setPosition({currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[5]->setPosition({currPos_.x + sz, currPos_.y + 2.f * sz});
			break;
		case Direction::LEFT:
			body_[0]->setPosition({currPos_.x + sz, currPos_.y});
			body_[1]->setPosition({currPos_.x + 2.f * sz, currPos_.y});
			body_[2]->setPosition({currPos_.x, currPos_.y + sz});
			body_[3]->setPosition({currPos_.x + sz, currPos_.y + sz});
			body_[4]->setPosition({currPos_.x + sz, currPos_.y + 2.f * sz});
			body_[5]->setPosition({currPos_.x + 2.f * sz, currPos_.y + 2.f * sz});
			break;
		case Direction::RIGHT:
			body_[0]->setPosition({currPos_.x, currPos_.y});
			body_[1]->setPosition({currPos_.x + sz, currPos_.y});
			body_[2]->setPosition({currPos_.x + sz, currPos_.y + sz});
			body_[3]->setPosition({currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[4]->setPosition({currPos_.x, currPos_.y + 2.f * sz});
			body_[5]->setPosition({currPos_.x + sz, currPos_.y + 2.f * sz});
			break;
		}
	}

	void Tank::setDirection(Direction dir)
	{
		MovingGameObject::setDirection(dir);
		turn(dir);
	}

	void Tank::makeShot()
	{
		Bullet* new_bullet = nullptr;

		const auto curr_pos = getPosition();
		const auto curr_sz = getSize();
		const auto curr_step = getStep();

		switch (getDirection()) {
			case Direction::FORWARD:
				new_bullet = new Bullet(curr_step, curr_sz, {curr_pos.x + curr_step, curr_pos.y});
				new_bullet->setFillColor(body_[0]->getFillColor());
				new_bullet->setBorderColor(body_[0]->getOutlineColor());
				new_bullet->setDirection(Direction::FORWARD);
				break;
			case Direction::BACKWARD:
				new_bullet = new Bullet(curr_step, curr_sz, {curr_pos.x + curr_step, curr_pos.y + 2.f * curr_sz});
				new_bullet->setFillColor(body_[0]->getFillColor());
				new_bullet->setBorderColor(body_[0]->getOutlineColor());
				new_bullet->setDirection(Direction::BACKWARD);
				break;
			case Direction::LEFT:
				new_bullet = new Bullet(curr_step, curr_sz, {curr_pos.x, curr_pos.y + curr_sz});
				new_bullet->setFillColor(body_[0]->getFillColor());
				new_bullet->setBorderColor(body_[0]->getOutlineColor());
				new_bullet->setDirection(Direction::LEFT);
				break;
			case Direction::RIGHT:
				new_bullet = new Bullet(curr_step, curr_sz, {curr_pos.x + 2.f * curr_sz, curr_pos.y + curr_sz});
				new_bullet->setFillColor(body_[0]->getFillColor());
				new_bullet->setBorderColor(body_[0]->getOutlineColor());
				new_bullet->setDirection(Direction::RIGHT);
				break;
		}

		if(new_bullet == nullptr) { return; }

		getGameEventsManager()->addGameObject(new_bullet);

		new_bullet->onDelete.connect(this, &Tank::deleteBullet);
		bullets_.push_back(new_bullet);
	}
	void Tank::makeStep()
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
		turn(getDirection());
	}

	void Tank::outOfScreenEvent(const sf::RenderWindow& win)
	{
		const auto curr_pos = getPosition();
		const auto curr_sz = getSize();
		const auto win_sz = win.getSize();
		switch (getDirection()) {
			case Direction::FORWARD:
				setPosition({curr_pos.x, win_sz.y - curr_sz});
				break;
			case Direction::BACKWARD:
				setPosition({curr_pos.x, -2.f * curr_sz});
				break;
			case Direction::LEFT:
				setPosition({win_sz.x - curr_sz, curr_pos.y});
				break;
			case Direction::RIGHT:
				setPosition({-2.f * curr_sz, curr_pos.y});
				break;
		}
		turn(getDirection());
	}

	void Tank::deleteBullet(GameObject* bullet)
	{
		bullets_.erase(
			std::remove(std::begin(bullets_), 
			std::end(bullets_), (Bullet*)bullet), 
			std::end(bullets_)
		);
	}

	void Tank::setFillColor(const sf::Color& color)
	{
		for(auto sh : body_) {
			sh->setFillColor(color);
		}
		for(auto b : bullets_) {
			b->setFillColor(color);
		}
	}

	void Tank::setBorderColor(const sf::Color& color)
	{
		for(auto sh : body_) {
			sh->setOutlineColor(color);
		}
		for(auto b : bullets_) {
			b->setBorderColor(color);
		}
	}

	void Tank::handleCollision(GameObject* obj)
	{
		assert(obj != nullptr && "obj ptr was null!");
		if(isDeleted() || obj->isDeleted()) {
			return;
		}

		if(obj->getType() == GameObjectType::BULLET) {
			auto bullet = dynamic_cast<Bullet*>(obj);
			assert(bullet != nullptr && "bullet ptr was null!");
			const auto& myBullets = getBullets();
			if(std::find(std::begin(myBullets), std::end(myBullets), bullet) 
					!= std::end(myBullets)) {
				return;
			}
			const sf::FloatRect bulletGeomentryRect(
				bullet->getPosition(),
				{bullet->getSize(), bullet->getSize()}
			);
			for(auto bodyRect : body_) {
				if(bodyRect->getGlobalBounds()
					.intersects(bulletGeomentryRect)) {
						this->deleteLater();
						bullet->deleteLater();
					}
			}
		}
		else if(obj->getType() == GameObjectType::TANK) {
			auto tank = dynamic_cast<Tank*>(obj);
			assert(tank != nullptr && "tank ptr was null!");

			for(auto thisBodyRect : body_) {
				for(auto tankBodyRect : tank->body_) {
					if(thisBodyRect->getGlobalBounds()
						.intersects(tankBodyRect->getGlobalBounds())) {
							this->deleteLater();
							tank->deleteLater();
							return;
						}
				}
			}
		}
	}
}