#pragma once

#include "Entity.hpp"
#include "World.hpp"

namespace nexc {

	bool Entity::isAlive() const {
		return world->generation[id] == generation;
	}

	template<typename T>
	inline void Entity::set(const T& value) {
		if (world->getComponentStorage<T>().set(id, value)) {
			auto fam = ComponentStorage<T>::getFamily();
			world->mask[id].set(fam, true);
		}
	}

	template<typename T>
	inline T Entity::get() {
		return world->getComponentStorage<T>().get(id);
	}

	template<typename T>
	inline void Entity::remove() {
		world->getComponentStorage<T>().remove(id);
		auto fam = ComponentStorage<T>::getFamily();
		world->mask[id].set(fam, false);
	}

}
