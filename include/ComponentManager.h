#pragma once
#include <unordered_map>
#include <unordered_set>
#include <typeindex>
#include <memory>
#include "Components.h"

using Entity = std::size_t;

// Component Manager to store and manage components of entities
class ComponentManager {
private:
    std::unordered_map<std::type_index, std::unordered_map<Entity, std::shared_ptr<void>>> components;

public:
    template <typename T>
    void addComponent(Entity entity, T component) {
        std::type_index typeIndex = std::type_index(typeid(T));
        components[typeIndex][entity] = std::make_shared<T>(component);
    }

    template <typename T>
    T* getComponent(Entity entity) {
        std::type_index typeIndex = std::type_index(typeid(T));
        if (components[typeIndex].find(entity) != components[typeIndex].end()) {
            return static_cast<T*>(components[typeIndex][entity].get());
        }
        return nullptr;
    }
};