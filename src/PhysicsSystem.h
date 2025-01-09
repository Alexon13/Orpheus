#pragma once
#include <unordered_map>
#include "Components.h"

class PhysicsSystem {
private:
    float gravity = 9.8f; // Gravity constant (adjust as needed)
    std::unordered_map<Entity, Position*> positions;
    std::unordered_map<Entity, Velocity*> velocities;
    std::unordered_map<Entity, Acceleration*> accelerations;
    std::unordered_map<Entity, Mass*> masses;

public:
    void addEntity(Entity entity, Position* pos, Velocity* vel, Acceleration* acc = nullptr, Mass* mass = nullptr) {
        positions[entity] = pos;
        velocities[entity] = vel;
        if (acc) accelerations[entity] = acc;
        if (mass) masses[entity] = mass;
    }

    void update(float deltaTime) {
        for (const auto& [entity, pos] : positions) {
            Velocity* vel = velocities[entity];
            Acceleration* acc = accelerations.count(entity) ? accelerations[entity] : nullptr;

            // Apply gravity to velocity
            if (masses.count(entity)) {
                vel->dy += gravity * deltaTime;
            }

            // Apply acceleration to velocity
            if (acc) {
                vel->dx += acc->ax * deltaTime;
                vel->dy += acc->ay * deltaTime;
            }

            // Update position based on velocity
            pos->x += vel->dx * deltaTime;
            pos->y += vel->dy * deltaTime;

            // Boundary check: prevent object from falling below screen (ground level at y = 600)
            if (pos->y + 50 > 600) { // Assuming object height = 50
                pos->y = 600 - 50;
                vel->dy = 0; // Stop vertical movement on collision with ground
            }
        }
    }
};