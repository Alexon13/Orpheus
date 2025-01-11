#include "EntityManager.h"

// Create a new entity
Entity EntityManager::createEntity() {
    Entity entity = nextEntityId++;
    entities.insert(entity);
    return entity;
}

// Remove an entity and all its components
void EntityManager::removeEntity(Entity entity) {
    entities.erase(entity);
    for (auto& [type, entityMap] : components) {
        entityMap.erase(entity);
    }
}

// Retrieve all active entities
const std::unordered_set<Entity>& EntityManager::getEntities() const {
    return entities;
}