Orpheus Engine

Project Overview:
The **Orpheus Engine** is a custom 2D game engine designed and implemented from scratch. It features core systems for managing entities, components, physics, rendering, and collision detection, along with debugging tools for visualizing the internal state of the engine.

---

# Features

## 1. Entity-Component System (ECS)
The engine uses an Entity-Component System (ECS) architecture to manage game objects and their behavior:

- *EntityManager*:
  - Manages the creation and destruction of entities.
  - Tracks active entities in the engine.

- *ComponentManager*:
  - Manages components for entities, allowing dynamic addition and retrieval.
  - Stores components such as `Position`, `Velocity`, `Size`, `Mass`, `Force`, and `Friction`.

## 2. Physics System
The *PhysicsSystem* updates the positions and velocities of entities based on forces, gravity, and friction. It handles:

- Gravity simulation.
- Force application.
- Friction effects.
- Boundary constraints to prevent entities from leaving the game area.
- Collision detection using the integrated **CollisionSystem**.
- Collision response with realistic physics (elastic collision and friction-based energy loss).

## 3. Collision System
The *CollisionSystem* detects and processes collisions between entities:

- Detects overlapping entities using their `Position` and `Size` components.
- Calls a collision handler to apply responses, such as reversing or adjusting velocities based on a friction coefficient during collisions.

## 4. Debug System
The *DebugSystem* provides visual tools for inspecting the state of the engine:

- Renders collision boxes around entities.
- Displays velocity and force vectors.
- Can be toggled on and off using the `D` key.

## 5. Rendering System
The *RenderingSystem* handles visual representation:

- Renders entities with their assigned colors or textures.
- Supports explicit rendering of specific entities for precise control.

---

# File Structure

- *main.cpp*: Entry point of the application; sets up the ECS and game loop.
- *EntityManager.h*: Manages entities and their lifecycle.
- *ComponentManager.h*: Handles component storage and retrieval.
- *Components.h*: Defines all the component types (e.g., `Position`, `Velocity`, etc.).
- *PhysicsSystem.h*: Updates entity states based on physics calculations.
- *CollisionSystem.h*: Detects and handles collisions between entities.
- *DebugSystem.h*: Renders debug information such as collision boxes and vectors.
- *RenderingSystem.h*: Manages the rendering of entities.

---

# Key Concepts

## Entity-Component System (ECS)
- *Entities*: Unique identifiers representing game objects.
- *Components*: Data structures that store information (e.g., position, velocity).
- *Systems*: Logic that operates on entities with specific components.

## Collision Handling
- *Elastic Collisions*: Conserves momentum and adjusts velocities of entities after a collision.
- *Friction Coefficient*: Simulates energy loss during collisions, ensuring more realistic physics.

---

# Controls

- *Toggle Debug Mode*: Press `D` to enable or disable visual debugging.

---

# How to Run

1. Clone the repository:
   git clone <repository-url>
   cd Orpheus

2. Build the project using CMake:
   cmake -S . -B build
   cmake --build build

3. Run the executable:
   ./build/OrpheusEngine

---

# Future Plans

- *Audio System*: Add support for sound effects and background music.
- *Spawning System*: Implement an entity spawning system with custom components.
- *Animation System*: Implement sprite-based animations.
- *Scripting System*: Introduce scripting for customizable entity behavior.
- *Advanced Physics*: Incorporate rotational physics and torque.

---

# Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests for improvements or new features.

---

# License
This project is licensed under the Apache License.

