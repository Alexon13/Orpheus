#pragma once
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <iostream>

// Entity type (unique identifier)
using Entity = std::size_t;

class EntityManager {
private:
    Entity nextEntityId = 0;
    std::vector<Entity> entities;

public:
    Entity createEntity() {
        Entity entity = nextEntityId++;
        entities.push_back(entity);
        std::cout << "Created Entity: " << entity << std::endl;
        return entity;
    }
};