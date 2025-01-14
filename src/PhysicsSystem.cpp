#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(EntityManager& em, ComponentManager& cm, WindowManager& wm)
    : entityManager(em), componentManager(cm), collisionSystem(cm), windowManager(wm) {}

void PhysicsSystem::addEntity(Entity entity) {
    entities.insert(entity);
    collisionSystem.addEntity(entity);
}

void PhysicsSystem::removeEntity(Entity entity) {
    entities.erase(entity);
    collisionSystem.removeEntity(entity);
}

// Update the physics with each frame
void PhysicsSystem::update(float deltaTime) {
    
    // Get window size information
    int window_width = windowManager.getScreenWidth();
    int window_height = windowManager.getScreenHeight();

    for (Entity entity : entities) {
        Position* pos = componentManager.getComponent<Position>(entity);
        Velocity* vel = componentManager.getComponent<Velocity>(entity);
        Mass* mass = componentManager.getComponent<Mass>(entity);
        Friction* friction = componentManager.getComponent<Friction>(entity);
        Force* force = componentManager.getComponent<Force>(entity);
        Size* size = componentManager.getComponent<Size>(entity);

        // Simulate Gravity
        if (pos && vel && mass && size) {
            if (gravityEnabled) {
                vel->dy += gravity * deltaTime; // Apply gravity if enabled
            }

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
            const float floorFriction = 0.01f; // Energy loss due to dragging on the floor (1%)

            if (pos->y + size->height > window_height) {
                vel->dx *= 1 - floorFriction;
            }

            // Logic for collisions with the walls
            const float wallFriction = 0.8f; // Energy loss for wall collisions (20%)

            if (pos->x < 0) { // Left wall
                pos->x = 0;
                vel->dx = -vel->dx * wallFriction;
            }
            if (pos->x + size->width > window_width) { // Right wall
                pos->x = window_width - size->width;
                vel->dx = -vel->dx * wallFriction;
            }
            if (pos->y < 0) { // Ceiling
                pos->y = 0;
                vel->dy = -vel->dy * wallFriction;
            }
            if (pos->y + size->height > window_height) { // Floor
                pos->y = window_height - size->height;
                vel->dy = -vel->dy * wallFriction / 1.5f; // Decrease velocity further when hitting the ground
            }
        }
    }

    // Update whenever a collision is detected
    collisionSystem.checkCollisions([this](Entity a, Entity b) {
        handleCollision(a, b);
    });
}

// Enable/Disable Gravity
void PhysicsSystem::toggleGravity() {
    gravityEnabled = !gravityEnabled;
}

// Handle collision between two entities
void PhysicsSystem::handleCollision(Entity a, Entity b) {
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