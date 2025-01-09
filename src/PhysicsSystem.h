#pragma once
#include "EntityManager.h"
#include "Components.h"
#include <unordered_set>

class PhysicsSystem {
private:
    std::unordered_set<Entity> entities;
    EntityManager& entityManager;
    ComponentManager& componentManager;

    float gravity = 9.8f; // Gravity constant for vertical motion

public:
    PhysicsSystem(EntityManager& em, ComponentManager& cm)
        : entityManager(em), componentManager(cm) {}

    void addEntity(Entity entity) {
        entities.insert(entity);
    }

    void removeEntity(Entity entity) {
        entities.erase(entity);
    }

    void update(float deltaTime) {
        for (Entity entity : entities) {
            // Fetch components from ComponentManager
            Position* pos = componentManager.getComponent<Position>(entity);
            Velocity* vel = componentManager.getComponent<Velocity>(entity);
            Mass* mass = componentManager.getComponent<Mass>(entity);
            Friction* friction = componentManager.getComponent<Friction>(entity);
            Force* force = componentManager.getComponent<Force>(entity);

            if (pos && vel && mass) {
                // Apply gravity to vertical velocity
                vel->dy += gravity * deltaTime;

                // Apply forces
                if (force) {
                    vel->dx += (force->fx / mass->value) * deltaTime;
                    vel->dy += (force->fy / mass->value) * deltaTime;
                }

                // Apply friction
                if (friction) {
                    vel->dx *= 1 - friction->coefficient;
                    vel->dy *= 1 - friction->coefficient;
                }

                // Update position based on velocity
                pos->x += vel->dx * deltaTime;
                pos->y += vel->dy * deltaTime;

                // Boundary checks
                if (pos->x < 0) { // Left wall
                    pos->x = 0;
                    vel->dx = 0;
                }
                if (pos->x + 50 > 800) { // Right wall (assuming width = 50)
                    pos->x = 800 - 50;
                    vel->dx = 0;
                }
                if (pos->y < 0) { // Ceiling
                    pos->y = 0;
                    vel->dy = 0;
                }
                if (pos->y + 50 > 600) { // Ground (assuming height = 50)
                    pos->y = 600 - 50;
                    vel->dy = 0;
                }
            }
        }
    }
};
