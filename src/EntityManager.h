#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include <typeinfo>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

#include "Entity.hpp"
class Entity;
class EntityManager {
public:

	template<typename T, typename... TArgs> T* create(TArgs&&... mArgs) {
		static_assert(std::is_base_of<Entity, T>::value, "T must be base of Entity");

		auto unique_ptr(std::make_unique<T>(std::forward<TArgs>(mArgs)...));
		T* ptr(unique_ptr.get());

		m_groupedEntities[typeid(T).hash_code()].push_back(ptr);
		m_entities.push_back(std::move(unique_ptr));

		return ptr;
	}

	template<typename T> std::vector<Entity*>& getAll() {
		return m_groupedEntities[typeid(T).hash_code()];
	}

	const std::vector<std::unique_ptr<Entity>>& getAllEntities();

	void remove(Entity* const);
	void refresh();
	void clear();

	static EntityManager* const Instance();

private:
	EntityManager();
	EntityManager(EntityManager const&);
	void operator=(EntityManager const&);

	std::vector<std::unique_ptr<Entity>> m_entities;
	std::map<std::size_t, std::vector<Entity*>> m_groupedEntities;
};

#endif