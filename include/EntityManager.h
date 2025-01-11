#pragma once
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <memory>
#include "Components.h"

using Entity = std::size_t;

class EntityManager {
private:
    Entity nextEntityId = 0;
    std::unordered_set<Entity> entities; // Track active entities
    std::unordered_map<std::type_index, std::unordered_map<Entity, std::shared_ptr<void>>> components;

public:
    // Create a new entity
    Entity createEntity();

    // Remove an entity and all its components
    void removeEntity(Entity entity);

    // Add a component to an entity
    template <typename T>
    void addComponent(Entity entity, const T& component);

    // Get a component from an entity
    template <typename T>
    T* getComponent(Entity entity);

    // Check if an entity has a specific component
    template <typename T>
    bool hasComponent(Entity entity);

    // Retrieve all active entities
    const std::unordered_set<Entity>& getEntities() const;
};

// Add a component to an entity
template <typename T>
void EntityManager::addComponent(Entity entity, const T& component) {
    components[typeid(T)][entity] = std::make_shared<T>(component);
}

// Get a component from an entity
template <typename T>
T* EntityManager::getComponent(Entity entity) {
    auto it = components.find(typeid(T));
    if (it != components.end() && it->second.find(entity) != it->second.end()) {
        return static_cast<T*>(it->second[entity].get());
    }
    return nullptr;
}

// Check if an entity has a specific component
template <typename T>
bool EntityManager::hasComponent(Entity entity) {
    auto it = components.find(typeid(T));
    return it != components.end() && it->second.find(entity) != it->second.end();
}