#include "SpawningSystem.h"

SpawningSystem::SpawningSystem(EntityManager& em, ComponentManager& cm, PhysicsSystem& ps)
    : entityManager(em), componentManager(cm), physicsSystem(ps) {}

// Spawn an entity with defined components
Entity SpawningSystem::spawnEntity(float x, float y, float dx, float dy, float width, float height, float mass, float friction) {
    Entity entity = entityManager.createEntity();

    componentManager.addComponent(entity, Position{x, y});
    componentManager.addComponent(entity, Velocity{dx, dy});
    componentManager.addComponent(entity, Size{width, height});
    componentManager.addComponent(entity, Mass{mass});
    componentManager.addComponent(entity, Friction{friction});
    componentManager.addComponent(entity, Force{0.0f, 0.0f}); // Set to 0 initially (TODO: Implement MovementSystem)

    physicsSystem.addEntity(entity);

    return entity;
}