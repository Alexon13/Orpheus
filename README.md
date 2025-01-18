# ⚙️ The Orpheus Engine ⚙️

The **Orpheus Engine** is a custom 2D game engine designed and implemented from scratch. It features core systems for managing entities, components, physics, rendering, and collision detection, along with debugging tools for visualizing the internal state of the engine.

---

- Author: *Lachezar Nikolov*
- GitHub: *LNikolov01*
- Email: *lnlachezarnikolov@gmail.com*

---

# Features

## 1️⃣ Entity-Component System (ECS)
The engine uses an Entity-Component System (ECS) architecture to manage game objects and their behavior:

- *EntityManager*:
  - Manages the creation and destruction of entities.
  - Tracks active entities in the engine.

- *ComponentManager*:
  - Manages components for entities, allowing dynamic addition and retrieval.
  - Stores components such as `Position`, `Velocity`, `Size`, `Mass`, `Force`, and `Friction`.

## 2️⃣ Physics System
The *PhysicsSystem* updates the positions and velocities of entities based on forces, gravity, and friction. It handles:

- Gravity simulation.
- Force application.
- Friction effects.
- Boundary constraints to prevent entities from leaving the game area.
- Collision detection using the integrated *CollisionSystem*.
- Collision response with realistic physics (elastic collision and friction-based energy loss).

## 3️⃣ Collision System
The *CollisionSystem* detects and processes collisions between entities:

- Detects overlapping entities using their `Position` and `Size` components.
- Calls a collision handler to apply responses, such as reversing or adjusting velocities based on a friction coefficient during collisions.

## 4️⃣ Debug System
The *DebugSystem* provides visual tools for inspecting the state of the engine:

- Renders collision boxes around entities.
- Displays velocity and force vectors.
- Can be toggled on and off using the `X` key.

## 5️⃣ Rendering System
The *RenderingSystem* handles visual representation:

- Renders entities with their assigned colors or textures.
- Supports explicit rendering of specific entities and their components for precise control.

## 6️⃣ Spawning System
The *SpawningSystem* handles spawning of entities:

- Controls the spawning of new entities and the assignment of their initial components.

## 7️⃣ Input System
The *InputSystem* handles the user input:

- Controls the input from the player and allows manual movement of entities.
- Controls the dev tools.

---

# File Structure

- *main.cpp*: Entry point of the application; sets up the ECS and game loop.
- *Components.h*: Defines all the component types (e.g., `Position`, `Velocity`, etc.).
- *EntityManager.h*: Manages entities and their lifecycle.
- *ComponentManager.h*: Handles component storage and retrieval.
- *WindowManager.h*: Used for simplified storage and retrieval of window settings.
- *PhysicsSystem.h*: Updates entity states based on physics calculations.
- *CollisionSystem.h*: Detects and handles collisions between entities.
- *SpawningSystem.h*: Manages the spawning of entities with different components.
- *InputSystem.h* : Manages input from the player.
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

# Controls (More to be added soon)

- *Toggle Debug Mode*: Press `X` to enable or disable visual debugging.
- *Toggle Gravity ON/OFF: Press `G` to enable or disable gravity.
- *Move Left*: Press `A` to move left.
- *Move Right*: Press `D` to move right.
- *Jump*: Press `SPACE` to jump. (Must be on the ground)

---

# Installation

## 1️⃣ Ensure SDL2 lib is installed

## 2️⃣ Clone the repository:
```bash
git clone https://github.com/LNikolov01/Orpheus.git
cd Orpheus
```

## 3️⃣ Build the project using CMake:
```bash
cmake -S . -B build
cmake --build build
```

## 4️⃣ Run the executable:
```bash
./build/Orpheus_Engine
```

---

# Future Plans

- ✅ *Scene System*: Implement a scene system that manages active scenes and transitions between them.
- ✅ *Audio System*: Add support for sound effects and background music.
- ✅ *Particle System*: Implement a particle system for specific events (like explosions).
- ✅ *Animation System*: Implement sprite-based animations.
- ✅ *Scripting System*: Introduce scripting for customizable entity behavior.
- ✅ *Advanced Physics*: Incorporate rotational physics and torque.

---

# Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests for improvements or new features.

---

# License
The Orpheus Engine is licensed under the Apache License.