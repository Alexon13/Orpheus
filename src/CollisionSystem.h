#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include "Components.h"

class CollisionSystem {
private:
    struct EntityData {
        Position* position;
        Size* size;
    };

    std::unordered_map<Entity, EntityData> entities;

public:
    void addEntity(Entity entity, Position* position, Size* size) {
        entities[entity] = { position, size };
    }

    void checkCollisions(const std::function<void(Entity, Entity)>& onCollision) {
        std::vector<Entity> entityList;
        for (const auto& [entity, data] : entities) {
            entityList.push_back(entity);
        }

        for (size_t i = 0; i < entityList.size(); ++i) {
            for (size_t j = i + 1; j < entityList.size(); ++j) {
                Entity a = entityList[i];
                Entity b = entityList[j];

                if (isColliding(entities[a], entities[b])) {
                    onCollision(a, b);
                }
            }
        }
    }

private:
    bool isColliding(const EntityData& a, const EntityData& b) {
        return (a.position->x < b.position->x + b.size->width &&
                a.position->x + a.size->width > b.position->x &&
                a.position->y < b.position->y + b.size->height &&
                a.position->y + a.size->height > b.position->y);
    }
};