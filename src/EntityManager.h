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
	EntityManager();

	template<typename T, typename... TArgs> T* create(TArgs&&... mArgs) {
		static_assert(std::is_base_of<Entity, T>::value, "T must be base of Entity");

		std::unique_ptr<T> uPtr(std::make_unique<T>(std::forward<TArgs>(mArgs)...));
		T* ptr(uPtr.get());

		//m_groupedEntities[typeid(T).hash_code()].push_back(ptr);
		//m_entities.emplace_back(std::move(uPtr));

//		auto uPtr(std::make_unique<T>(std::forward<TArgs>(mArgs)...));
//		auto ptr(uPtr.get());
		m_groupedEntities[typeid(T).hash_code()].emplace_back(ptr);
		m_entities.emplace_back(std::move(uPtr));

		return ptr;
	}

	template<typename T> std::vector<Entity*>& getAll() {
		return m_groupedEntities[typeid(T).hash_code()];
	}

	void refresh();
	void clear();

public:
	static EntityManager* Instance;

private:
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::map<std::size_t, std::vector<Entity*>> m_groupedEntities;
};

#endif