#pragma once
#include "EntityManager.h"
#include "Components.h"
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

            if (pos && vel && mass) {
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

                if (pos->x < 0) {
                    pos->x = 0;
                    vel->dx = -vel->dx;
                }
                if (pos->x + 50 > 800) {
                    pos->x = 800 - 50;
                    vel->dx = -vel->dx;
                }
                if (pos->y < 0) {
                    pos->y = 0;
                    vel->dy = -vel->dy;
                }
                if (pos->y + 50 > 600) {
                    pos->y = 600 - 50;
                    vel->dy = -vel->dy;
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

        if (velA && velB && massA && massB) {
            float mA = massA->value;
            float mB = massB->value;

            // Calculate new velocities using the elastic collision equations
            float newVelA_X = (velA->dx * (mA - mB) + 2 * mB * velB->dx) / (mA + mB);
            float newVelB_X = (velB->dx * (mB - mA) + 2 * mA * velA->dx) / (mA + mB);

            float newVelA_Y = (velA->dy * (mA - mB) + 2 * mB * velB->dy) / (mA + mB);
            float newVelB_Y = (velB->dy * (mB - mA) + 2 * mA * velA->dy) / (mA + mB);

            // Update velocities
            velA->dx = newVelA_X;
            velA->dy = newVelA_Y;
            velB->dx = newVelB_X;
            velB->dy = newVelB_Y;
        }
    }
};