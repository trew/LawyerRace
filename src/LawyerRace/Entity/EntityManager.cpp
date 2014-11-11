#include "LawyerRace/Entity/EntityManager.hpp"
#include "LawyerRace/Entity/Entity.hpp"

EntityManager::EntityManager() {
}

const std::vector<std::unique_ptr<Entity>>& EntityManager::getAllEntities() {
	return m_entities;
}

void EntityManager::refresh() {
	for (auto& pair : m_groupedEntities)
	{
		auto& vector(pair.second);

		vector.erase(
			std::remove_if(std::begin(vector), std::end(vector),
			[](Entity* mPtr){
			return mPtr->m_shouldBeRemoved;
		}),
			std::end(vector));
	}

	m_entities.erase(
		std::remove_if(std::begin(m_entities), std::end(m_entities),
		[](const std::unique_ptr<Entity>& mUPtr){ return mUPtr->m_shouldBeRemoved; }),
		std::end(m_entities));
}

void EntityManager::remove(Entity* e) {
	e->m_shouldBeRemoved = true;
}

void EntityManager::clear() {
	m_entities.clear();
	m_groupedEntities.clear();
}