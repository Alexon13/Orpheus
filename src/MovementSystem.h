#pragma once
#include "Components.h"
#include "EntityManager.h"
#include <unordered_map>

class MovementSystem {
private:
    std::unordered_map<Entity, Position*> positions;
    std::unordered_map<Entity, Velocity*> velocities;

public:
    void addEntity(Entity entity, Position* pos, Velocity* vel) {
        positions[entity] = pos;
        velocities[entity] = vel;
    }

    void update(float deltaTime) {
        for (const auto& [entity, pos] : positions) {
            Velocity* vel = velocities[entity];
            pos->x += vel->dx * deltaTime;
            pos->y += vel->dy * deltaTime;
        }
    }
};