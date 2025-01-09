#pragma once
#include <unordered_set>
#include <functional>
#include "Components.h"
#include "EntityManager.h"

class CollisionSystem {
private:
    ComponentManager& componentManager;
    std::unordered_set<Entity> entities;

public:
    explicit CollisionSystem(ComponentManager& cm) : componentManager(cm) {}

    void addEntity(Entity entity) {
        entities.insert(entity);
    }

    void removeEntity(Entity entity) {
        entities.erase(entity);
    }

    void checkCollisions(const std::function<void(Entity, Entity)>& onCollision) {
        for (auto it1 = entities.begin(); it1 != entities.end(); ++it1) {
            for (auto it2 = std::next(it1); it2 != entities.end(); ++it2) {
                Entity a = *it1;
                Entity b = *it2;

                Position* posA = componentManager.getComponent<Position>(a);
                Size* sizeA = componentManager.getComponent<Size>(a);
                Position* posB = componentManager.getComponent<Position>(b);
                Size* sizeB = componentManager.getComponent<Size>(b);

                if (posA && sizeA && posB && sizeB && isColliding(posA, sizeA, posB, sizeB)) {
                    onCollision(a, b);
                }
            }
        }
    }

private:
    bool isColliding(Position* posA, Size* sizeA, Position* posB, Size* sizeB) {
        return (posA->x < posB->x + sizeB->width &&
                posA->x + sizeA->width > posB->x &&
                posA->y < posB->y + sizeB->height &&
                posA->y + sizeA->height > posB->y);
    }
};