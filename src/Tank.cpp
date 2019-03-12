#include "Tank.hpp"

namespace tf
{

	Tank::Tank()
		: MovingGameObject()
		, body_{6}
	{
		for(std::size_t i = 0; i < body_.size(); ++i) {
			body_[i] = new sf::RectangleShape();
			body_[i]->setFillColor(sf::Color(220, 20, 60));
			body_[i]->setOutlineColor(sf::Color(144, 0, 32));
		}

		timer_->onTimerCall.connect(this, &Tank::makeStep);
		timer_->start(1000);
	}
	Tank::Tank(sf::Vector2f pos, sf::Vector2f sz)
		: MovingGameObject()
		, body_{6}
	{
		for(std::size_t i = 0; i < body_.size(); ++i) {
			body_[i] = new sf::RectangleShape(sz);
			body_[i]->setFillColor(sf::Color(220, 20, 60));
			body_[i]->setOutlineColor(sf::Color(144, 0, 32));
			body_[i]->setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		}
		setPosition(pos);

		timer_->onTimerCall.connect(this, &Tank::makeStep);
		timer_->start(1000);
	}
	Tank::Tank(sf::Vector2f pos, sf::Vector2f sz, sf::Vector2f d)
		: MovingGameObject(d)
		, body_{6}
	{
		for(std::size_t i = 0; i < body_.size(); ++i) {
			body_[i] = new sf::RectangleShape(sz);
			body_[i]->setFillColor(sf::Color(220, 20, 60));
			body_[i]->setOutlineColor(sf::Color(144, 0, 32));
			body_[i]->setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		}
		setPosition(pos);

		timer_->onTimerCall.connect(this, &Tank::makeStep);
		timer_->start(1000);
	}

	Tank::~Tank()
	{
		for(auto sh : body_) {
			delete sh;
		}

		for(auto b : bullets_) {
			delete b;
		}
	}

	void Tank::draw(sf::RenderWindow& w)
	{
		for(auto sh : body_) {
			w.draw(*sh);
		}
	}

	sf::Vector2f Tank::getSize() const
	{
		return body_[0]->getSize();
	}
	void Tank::setSize(sf::Vector2f sz)
	{
		for(auto sh : body_) {
			sh->setSize(sz);
			sh->setOutlineThickness(-((sz.x + sz.y) / 2.f) / 9.f);
		}
		setPosition(getPosition());
	}

	sf::Vector2f Tank::getPosition() const
	{
		auto pos = body_[0]->getPosition();
		auto sz = body_[0]->getSize();
		pos.x -= sz.x;
		return pos;
	}
	void Tank::setPosition(sf::Vector2f pos)
	{
		const auto sz = getSize();
		body_[0]->setPosition({pos.x + sz.x, pos.y});
		body_[1]->setPosition({pos.x, pos.y + sz.y});
		body_[2]->setPosition({pos.x + sz.x, pos.y + sz.y});
		body_[3]->setPosition({pos.x + sz.x * 2.f, pos.y + sz.y});
		body_[4]->setPosition({pos.x, pos.y + sz.y * 2.f});
		body_[5]->setPosition({pos.x + sz.x * 2.f, pos.y + sz.y * 2.f});
	}

	void Tank::makeShot()
	{
	}
	void Tank::makeStep()
	{
		setPosition(getPosition() + getDelta());
	}

	const std::vector<Bullet*>& Tank::getBullets()
	{
		return bullets_;
	}

}