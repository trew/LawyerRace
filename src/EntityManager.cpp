#include "EntityManager.h"

EntityManager* EntityManager::Instance;

EntityManager::EntityManager() {
	Instance = this;
}

void EntityManager::refresh() {
	for (auto& pair : m_groupedEntities)
	{
		auto& vector(pair.second);

		vector.erase(
			std::remove_if(std::begin(vector), std::end(vector),
			[](Entity* mPtr){
			return mPtr->m_destroyed;
		}),
			std::end(vector));
	}

	m_entities.erase(
		std::remove_if(std::begin(m_entities), std::end(m_entities),
		[](const std::unique_ptr<Entity>& mUPtr){ return mUPtr->m_destroyed; }),
		std::end(m_entities));
}

void EntityManager::clear() {
	m_entities.clear();
	m_groupedEntities.clear();
}