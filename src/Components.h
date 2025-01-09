#pragma once

struct Position {
    float x, y; // Position of an entity
};

struct Velocity {
    float dx, dy; // Velocity in terms of x and y
};

struct Size {
    float width, height; // Size of entity
};

struct Acceleration {
    float ax, ay; // Acceleration in x and y directions
};

struct Mass {
    float value; // Mass of the entity (used for physics calculations)
};

struct Friction {
    float coefficient; // Friction coefficient (0 = no friction, 1 = full stop)
};

struct Force {
    float fx, fy; // Applied force in x and y directions
};