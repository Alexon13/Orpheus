#pragma once

struct Position {
    float x, y; // Current Position of an entity
};

struct Velocity {
    float dx, dy; // Current Velocity in terms of x and y
};

struct Size {
    float width, height; // Size of an entity
};

struct Acceleration {
    float ax, ay; // Current Acceleration in x and y directions
};

struct Mass {
    float value; // Mass of the entity (used for physics calculations)
};

struct Friction {
    float coefficient; // Friction coefficient applied (0 = no friction, 1 = full stop)
};

struct Force {
    float fx, fy; // Applied force in x and y directions
};