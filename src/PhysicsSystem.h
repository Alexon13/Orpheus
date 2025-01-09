#pragma once
#include <unordered_map>
#include "Components.h"

class PhysicsSystem {
private:
    float gravity = 9.8f; // Gravity constant
    std::unordered_map<Entity, Position*> positions;
    std::unordered_map<Entity, Velocity*> velocities;
    std::unordered_map<Entity, Acceleration*> accelerations;
    std::unordered_map<Entity, Mass*> masses;
    std::unordered_map<Entity, Friction*> frictions;
    std::unordered_map<Entity, Force*> forces;

public:
    void addEntity(Entity entity, Position* pos, Velocity* vel, Acceleration* acc = nullptr, Mass* mass = nullptr, Friction* friction = nullptr, Force* force = nullptr) {
        positions[entity] = pos;
        velocities[entity] = vel;
        if (acc) accelerations[entity] = acc;
        if (mass) masses[entity] = mass;
        if (friction) frictions[entity] = friction;
        if (force) forces[entity] = force;
    }

    void update(float deltaTime) {
        for (const auto& [entity, pos] : positions) {
            Velocity* vel = velocities[entity];
            Acceleration* acc = accelerations.count(entity) ? accelerations[entity] : nullptr;
            Friction* friction = frictions.count(entity) ? frictions[entity] : nullptr;
            Force* force = forces.count(entity) ? forces[entity] : nullptr;

            // Apply gravity to velocity
            if (masses.count(entity)) {
                vel->dy += gravity * deltaTime;
            }

            // Apply acceleration to velocity
            if (acc) {
                vel->dx += acc->ax * deltaTime;
                vel->dy += acc->ay * deltaTime;
            }

            // Apply forces to velocity
            if (force) {
                vel->dx += (force->fx / masses[entity]->value) * deltaTime;
                vel->dy += (force->fy / masses[entity]->value) * deltaTime;
            }

            // Apply friction to velocity
            if (friction) {
                vel->dx *= 1 - friction->coefficient;
                vel->dy *= 1 - friction->coefficient;
            }

            // Update position based on velocity
            pos->x += vel->dx * deltaTime;
            pos->y += vel->dy * deltaTime;

            // Prevent falling through ground (simple collision with ground)
            if (pos->y + 50 > 600) { // Assuming object height = 50
                pos->y = 600 - 50;
                vel->dy = 0; // Stop vertical movement
            }
        }
    }
};