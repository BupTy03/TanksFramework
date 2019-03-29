#include "GameEventsManager.hpp"

#include <SFML/Window.hpp>

#include <iostream>
#include <algorithm>

namespace tf
{

	GameEventsManager& GameEventsManager::Instance()
	{
		static GameEventsManager instance;
		return instance;
	}

	void GameEventsManager::collectDeleted()
	{
		objects_.erase(std::remove_if(std::begin(objects_), std::end(objects_), [](auto p) {
			if(p->isDeleted()) {
				delete p;
				return true;
			}
			return false;
		}), std::end(objects_));
	}

	void GameEventsManager::handleKeyEvents(sf::Keyboard::Key key)
	{
		for(std::size_t i = 0; i < objects_.size(); ++i) {
			objects_[i]->keyEvent(key);
		}
	}

	void GameEventsManager::processOutOfScreenEvents()
	{
		if(!window_) {
			return;
		}
		const auto win_sz = window_->getSize();
		for(std::size_t i = 0; i < objects_.size(); ++i) {
			const auto pos = objects_[i]->getPosition();
			const auto sz = objects_[i]->getSize();
			if(pos.x < -3.f * sz || pos.y < -3.f * sz || 
				pos.x > win_sz.x || pos.y > win_sz.y) {
				objects_[i]->outOfScreenEvent();
			}
		}
	}

	void GameEventsManager::processEvents()
	{
		processOutOfScreenEvents();
		collectDeleted();

		sf::Event event;
		sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;
		while (window_->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window_->close();
				return;
			}
			if(event.type == sf::Event::KeyPressed) {
				key = event.key.code;
			}
		}
		if(key != sf::Keyboard::Key::Unknown) {
			handleKeyEvents(key);
		}
	}

	void GameEventsManager::addGameObject(GameObject* obj)
	{
		if(obj == nullptr) {
			return;
		}
		if(std::cend(objects_) == std::find(std::cbegin(objects_), std::cend(objects_), obj)) {
			objects_.push_back(obj);
		}
	}

	void GameEventsManager::removeGameObject(GameObject* obj)
	{
		if(obj == nullptr) {
			return;
		}
		objects_.erase(
			std::remove(std::begin(objects_), std::end(objects_), obj), std::end(objects_)
		);
	}

}