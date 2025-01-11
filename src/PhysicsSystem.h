#pragma once
#include "Components.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "CollisionSystem.h"
#include <unordered_set>

class PhysicsSystem {
private:
    std::unordered_set<Entity> entities;
    EntityManager& entityManager;
    ComponentManager& componentManager;
    CollisionSystem collisionSystem;

    float gravity = 9.8f; // Gravity constant

public:
    PhysicsSystem(EntityManager& em, ComponentManager& cm)
        : entityManager(em), componentManager(cm), collisionSystem(cm) {}

    void addEntity(Entity entity) {
        entities.insert(entity);
        collisionSystem.addEntity(entity);
    }

    void removeEntity(Entity entity) {
        entities.erase(entity);
        collisionSystem.removeEntity(entity);
    }

    // Get components and keep with updating each frame
    void update(float deltaTime) {
        for (Entity entity : entities) {
            Position* pos = componentManager.getComponent<Position>(entity);
            Velocity* vel = componentManager.getComponent<Velocity>(entity);
            Mass* mass = componentManager.getComponent<Mass>(entity);
            Friction* friction = componentManager.getComponent<Friction>(entity);
            Force* force = componentManager.getComponent<Force>(entity);
            Size* size = componentManager.getComponent<Size>(entity);

            // Simulate Gravity
            if (pos && vel && mass && size) {
                vel->dy += gravity * deltaTime;

                if (force) {
                    vel->dx += (force->fx / mass->value) * deltaTime;
                    vel->dy += (force->fy / mass->value) * deltaTime;
                }

                if (friction) {
                    vel->dx *= 1 - friction->coefficient;
                    vel->dy *= 1 - friction->coefficient;
                }

                pos->x += vel->dx * deltaTime;
                pos->y += vel->dy * deltaTime;

                // Logic for dragging on the floor
                const float floorFriction = 0.001f; // Energy loss due to dragging on the floor (1%)

                if (pos->y + size->height > 600) {
                    vel->dx *= 1 - floorFriction;
                }

                // Logic for collisions with the walls
                const float wallFriction = 0.8f; // Energy loss for wall collisions (20%)

                if (pos->x < 0) { // Left wall
                    pos->x = 0;
                    vel->dx = -vel->dx * wallFriction;
                }
                if (pos->x + size->width > 800) { // Right wall
                    pos->x = 800 - size->width;
                    vel->dx = -vel->dx * wallFriction;
                }
                if (pos->y < 0) { // Ceiling
                    pos->y = 0;
                    vel->dy = -vel->dy * wallFriction;
                }
                if (pos->y + size->height > 600) { // Floor
                    pos->y = 600 - size->height;
                    vel->dy = -vel->dy * wallFriction / 2; // Decrease velocity further when hitting the ground
                }
            }
        }
        
        // Update whenever a collision is detected
        collisionSystem.checkCollisions([this](Entity a, Entity b) {
            handleCollision(a, b);
        });
    }

private:
    // Handle Collisions between two entities using (updated to reflect mass)
    void handleCollision(Entity a, Entity b) {
        Velocity* velA = componentManager.getComponent<Velocity>(a);
        Velocity* velB = componentManager.getComponent<Velocity>(b);
        Mass* massA = componentManager.getComponent<Mass>(a);
        Mass* massB = componentManager.getComponent<Mass>(b);

        // Friction coefficient for collisions (e.g., 0.9 for 10% energy loss)
        const float collisionFriction = 0.9f;

        if (velA && velB && massA && massB) {
            float mA = massA->value;
            float mB = massB->value;

            // Calculate new velocities using the elastic collision equations
            float newVelA_X = (velA->dx * (mA - mB) + 2 * mB * velB->dx) / (mA + mB);
            float newVelB_X = (velB->dx * (mB - mA) + 2 * mA * velA->dx) / (mA + mB);

            float newVelA_Y = (velA->dy * (mA - mB) + 2 * mB * velB->dy) / (mA + mB);
            float newVelB_Y = (velB->dy * (mB - mA) + 2 * mA * velA->dy) / (mA + mB);

            // Update velocities (with energy loss)
            velA->dx = newVelA_X * collisionFriction;
            velA->dy = newVelA_Y * collisionFriction;
            velB->dx = newVelB_X * collisionFriction;
            velB->dy = newVelB_Y * collisionFriction;
        }
    }
};