#pragma once

#include <bitset>
#include <unordered_map>

#include "MathUtil.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ECSEngine {

// This is a top-left location of an entity all other stored locations are relative to this
// location. This means that moving this single location will move anything else which is relative
// to the location such as:
// - sprite bounding boxes
// - collision bounding boxes
struct LocationComponent {
    Point2D loc;
    LocationComponent(Point2D p) : loc(p) {} 
    LocationComponent(float x = 0.f, float y = 0.f){
        loc = {x, y};
    }
};

struct MovementComponent {
    Point2D velocity;  // Velocity in pixels per second
    MovementComponent(Point2D v) : velocity(v) {}
    MovementComponent(float dx = 0, float dy = 0) {
        velocity = {dx, dy};
    }
};

struct GravityComponent {
    GravityComponent(Point2D acceleration, int disabledTimer = 0)
        : acceleration(acceleration), disabledTimer(disabledTimer) {}
    Point2D acceleration;  // Acceleration in pixels per second squared
    int disabledTimer;
};

// location for respawning
struct RespawnComponent {
    Point2D loc;
    RespawnComponent(Point2D spawnPoint = {0.f, 0.f}) {
        loc = spawnPoint;
    }
};

}  // namespace ECSEngine
