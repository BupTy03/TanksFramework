#include "GameEventsManager.hpp"

#include <algorithm>

namespace tf
{

	GameEventsManager* GameEventsManager::instance_ = nullptr;

	GameEventsManager& GameEventsManager::Instance()
	{
		if(instance_ == nullptr) {
			instance_ = new GameEventsManager();
		}
		return *instance_;
	}

	void GameEventsManager::processEvents()
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
			delete *it;
		}

		objects_.erase(begIt, endIt);
	}

	GameEventsManager::~GameEventsManager()
	{
		if(instance_ != nullptr) {
			delete instance_;
		}
	}

}