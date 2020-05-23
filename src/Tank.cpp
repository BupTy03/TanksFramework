#include "Tank.hpp"
#include "Wall.hpp"

#include <algorithm>
#include <cassert>


namespace tf
{

	Tank::Tank()
		: MovingGameObject{GameObjectType::TANK} 
		, body_()
		, bullets_()
		, currPos_()
	{
		for(auto& segment : body_) {
			segment.setFillColor(sf::Color{23, 164, 113});
			segment.setOutlineColor(sf::Color{31, 87, 67});
		}

		turn(getDirection());
	}

	void Tank::draw(sf::RenderWindow& win)
	{
		for(const auto& sh : body_) {
			win.draw(sh);
		}
		for(auto bullet : bullets_) {
			bullet->draw(win);
		}
	}

	float Tank::getSize() const 
	{ 
		return (body_.front()).getSize().x; 
	}

	void Tank::setSize(float sz)
	{
		for(auto& sh : body_) {
			sh.setSize(sf::Vector2f{sz, sz});
			sh.setOutlineThickness(-sz / 9.f);
		}
		turn(getDirection());
	}

	sf::Vector2f Tank::getPosition() const 
	{ 
		return currPos_;
	}

	void Tank::setPosition(const sf::Vector2f& pos) 
	{ 
		currPos_ = pos;
	}

	void Tank::turn(Direction dir)
	{
		const auto sz = getSize();
		switch (dir) {
		case Direction::FORWARD:
			body_[0].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y});
			body_[1].setPosition(sf::Vector2f{currPos_.x, currPos_.y + sz});
			body_[2].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y + sz});
			body_[3].setPosition(sf::Vector2f{currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[4].setPosition(sf::Vector2f{currPos_.x, currPos_.y + 2.f * sz});
			body_[5].setPosition(sf::Vector2f{currPos_.x + 2.f * sz, currPos_.y + 2.f * sz});
			break;
		case Direction::BACKWARD:
			body_[0].setPosition(sf::Vector2f{currPos_.x, currPos_.y});
			body_[1].setPosition(sf::Vector2f{currPos_.x + 2.f * sz, currPos_.y});
			body_[2].setPosition(sf::Vector2f{currPos_.x, currPos_.y + sz});
			body_[3].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y + sz});
			body_[4].setPosition(sf::Vector2f{currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[5].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y + 2.f * sz});
			break;
		case Direction::LEFT:
			body_[0].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y});
			body_[1].setPosition(sf::Vector2f{currPos_.x + 2.f * sz, currPos_.y});
			body_[2].setPosition(sf::Vector2f{currPos_.x, currPos_.y + sz});
			body_[3].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y + sz});
			body_[4].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y + 2.f * sz});
			body_[5].setPosition(sf::Vector2f{currPos_.x + 2.f * sz, currPos_.y + 2.f * sz});
			break;
		case Direction::RIGHT:
			body_[0].setPosition(sf::Vector2f{currPos_.x, currPos_.y});
			body_[1].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y});
			body_[2].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y + sz});
			body_[3].setPosition(sf::Vector2f{currPos_.x + 2.f * sz, currPos_.y + sz});
			body_[4].setPosition(sf::Vector2f{currPos_.x, currPos_.y + 2.f * sz});
			body_[5].setPosition(sf::Vector2f{currPos_.x + sz, currPos_.y + 2.f * sz});
			break;
		default:
			break;
		}
	}

	const std::vector<Bullet*>& Tank::getBullets() const
	{ 
		return bullets_; 
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
				new_bullet = new Bullet(curr_step, curr_sz, sf::Vector2f{curr_pos.x + curr_step, curr_pos.y});
				new_bullet->setFillColor(body_[0].getFillColor());
				new_bullet->setBorderColor(body_[0].getOutlineColor());
				new_bullet->setDirection(Direction::FORWARD);
				break;
			case Direction::BACKWARD:
				new_bullet = new Bullet(curr_step, curr_sz, sf::Vector2f{curr_pos.x + curr_step, curr_pos.y + 2.f * curr_sz});
				new_bullet->setFillColor(body_[0].getFillColor());
				new_bullet->setBorderColor(body_[0].getOutlineColor());
				new_bullet->setDirection(Direction::BACKWARD);
				break;
			case Direction::LEFT:
				new_bullet = new Bullet(curr_step, curr_sz, sf::Vector2f{curr_pos.x, curr_pos.y + curr_sz});
				new_bullet->setFillColor(body_[0].getFillColor());
				new_bullet->setBorderColor(body_[0].getOutlineColor());
				new_bullet->setDirection(Direction::LEFT);
				break;
			case Direction::RIGHT:
				new_bullet = new Bullet(curr_step, curr_sz, sf::Vector2f{curr_pos.x + 2.f * curr_sz, curr_pos.y + curr_sz});
				new_bullet->setFillColor(body_[0].getFillColor());
				new_bullet->setBorderColor(body_[0].getOutlineColor());
				new_bullet->setDirection(Direction::RIGHT);
				break;
			default:
				break;
		}

		if(new_bullet == nullptr) { return; }

		getGameEventsManager()->addGameObject(new_bullet);

		new_bullet->onDelete.connect(this, &Tank::deleteBullet);
		bullets_.emplace_back(new_bullet);
	}

	void Tank::makeStep()
	{
		const auto ps = getPosition();
		const auto step = getStep();
		switch (getDirection())
		{
			case Direction::FORWARD:
				setPosition(sf::Vector2f{ps.x, ps.y - step});
				break;
			case Direction::BACKWARD:
				setPosition(sf::Vector2f{ps.x, ps.y + step});
				break;
			case Direction::LEFT:
				setPosition(sf::Vector2f{ps.x - step, ps.y});
				break;
			case Direction::RIGHT:
				setPosition(sf::Vector2f{ps.x + step, ps.y});
				break;
			default:
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
				setPosition(sf::Vector2f{curr_pos.x, win_sz.y - curr_sz});
				break;
			case Direction::BACKWARD:
				setPosition(sf::Vector2f{curr_pos.x, -2.f * curr_sz});
				break;
			case Direction::LEFT:
				setPosition(sf::Vector2f{win_sz.x - curr_sz, curr_pos.y});
				break;
			case Direction::RIGHT:
				setPosition(sf::Vector2f{-2.f * curr_sz, curr_pos.y});
				break;
			default:
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
		for(auto& sh : body_) {
			sh.setFillColor(color);
		}
		for(auto b : bullets_) {
			b->setFillColor(color);
		}
	}

	sf::Color Tank::getFillColor() const 
	{ 
		return (body_.front()).getFillColor(); 
	}

	void Tank::setBorderColor(const sf::Color& color)
	{
		for(auto& sh : body_) {
			sh.setOutlineColor(color);
		}
		for(auto b : bullets_) {
			b->setBorderColor(color);
		}
	}

	sf::Color Tank::getBorderColor() const 
	{ 
		return (body_.front()).getOutlineColor(); 
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
				if(bodyRect.getGlobalBounds()
					.intersects(bulletGeomentryRect)) {
						this->deleteLater();
						bullet->deleteLater();
					}
			}
		}
		else if(obj->getType() == GameObjectType::TANK) {
			auto tank = dynamic_cast<Tank*>(obj);
			assert(tank != nullptr && "tank ptr was null!");

			for(const auto& thisBodyRect : body_) {
				for(const auto& tankBodyRect : tank->body_) {
					if(thisBodyRect.getGlobalBounds()
						.intersects(tankBodyRect.getGlobalBounds())) {
							this->deleteLater();
							tank->deleteLater();
							return;
						}
				}
			}
		}
	}
}
