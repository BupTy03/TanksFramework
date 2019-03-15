#include "GameEventsManager.hpp"

#include <SFML/Window.hpp>

#include <algorithm>

namespace tf
{

	GameEventsManager* GameEventsManager::instance_ = nullptr;

	GameEventsManager::GameEventsManager()
	{
	}

	GameEventsManager& GameEventsManager::Instance()
	{
		if(instance_ == nullptr) {
			instance_ = new GameEventsManager();
		}
		return *instance_;
	}

	void GameEventsManager::collectDeleted()
	{
		auto endIt = std::end(objects_);
		auto begIt = std::remove_if(std::begin(objects_), endIt, [](auto p){
			return p->isDeleted();
		});

		if(begIt == endIt) {
			return;
		}

		for(auto it = begIt; it != endIt; ++it) {
			(*it)->onDelete();
			delete (*it);
		}

		objects_.erase(begIt, endIt);
	}

	void GameEventsManager::handleKeyEvents(sf::Keyboard::Key key)
	{
		for(auto obj : objects_) {
			obj->keyEvent(key);
		}
	}

	void GameEventsManager::processOutOfScreenEvents()
	{
		for(auto obj : objects_) {
			const auto pos = obj->getPosition();
			const auto sz = obj->getSize();
			if(pos.x < -3.f * sz || pos.y < -3.f * sz || 
				pos.x > winSz_.x || pos.y > winSz_.y) {
				obj->outOfScreenEvent();
			}
		}
	}

	void GameEventsManager::processKeyEvents()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			handleKeyEvents(sf::Keyboard::A);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			handleKeyEvents(sf::Keyboard::D);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			handleKeyEvents(sf::Keyboard::S);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			handleKeyEvents(sf::Keyboard::W);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			handleKeyEvents(sf::Keyboard::Space);
		}
	}

	void GameEventsManager::processEvents()
	{
		processKeyEvents();
		processOutOfScreenEvents();
		collectDeleted();
	}

	std::size_t GameEventsManager::countObjects()
	{
		return objects_.size();
	}

	GameEventsManager::~GameEventsManager()
	{
		if(instance_ != nullptr) {
			delete instance_;
		}
		instance_ = nullptr;
	}

	void GameEventsManager::setWindowSize(sf::Vector2f sz)
	{
		winSz_ = sz;
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