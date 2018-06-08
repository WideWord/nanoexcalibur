#pragma once

#include "Entity.hpp"
#include "World.hpp"

namespace nexc {

	bool Entity::isAlive() const {
		if (id == maxEntitiesNum) return false;
		return world->generation[id] == generation;
	}

	template<typename T>
	inline Entity& Entity::set(const T& value) {
		if (world->getComponentStorage<T>().set(id, value)) {
			auto fam = ComponentStorage<T>::getFamily();
			world->mask[id].set(fam, true);
			world->emitEvent(ComponentAddedEvent<T>(*this));
		}
		world->emitEvent(ComponentUpdatedEvent<T>(*this));
		return *this;
	}

	template<typename T>
	inline T Entity::get() {
		return world->getComponentStorage<T>().get(id);
	}

	template<typename T>
	inline Entity& Entity::remove() {
		world->getComponentStorage<T>().remove(id);
		auto fam = ComponentStorage<T>::getFamily();
		world->mask[id].set(fam, false);
		world->emitEvent(ComponentRemovedEvent<T>(*this));
		return *this;
	}

	template<typename T>
	inline bool Entity::has() {
		if (!isAlive()) return false;
		return world->mask[id][ComponentStorage<T>::getFamily()];
	}

}
