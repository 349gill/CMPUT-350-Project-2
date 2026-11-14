#pragma once

#include <unordered_map>

#include "Entity.h"
#include "LocationComponent.h"
#include "MathUtil.h"
#include "SpriteComponent.h"
#include "SystemManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ECSEngine {

struct CameraComponent {
    Point2D position;  // [world coordinates] position in world coordinates
    float worldUnitsPerPixel;
    Rect hardExclusion;  // [screen coordinates] Area where the camera is not allowed to go
                         // (negative of this rect)
    Rect softExclusion;  // [screen coordinates] Area where the camera is allowed to go (but will
                         // scroll out)
    float speed;

    CameraComponent() {
        position = {0.f, 0.f}; // init at 0, 0 
        worldUnitsPerPixel = 1.f; // init at 1
        hardExclusion = {};
        softExclusion = {};
        speed = 0.f; // start stationary
    }
};

struct CameraFollower {
    EntityID entityID;  // The entity that this camera follows

    CameraFollower(EntityID id) {
        entityID = id;
    }
};

struct CameraShake {
    int frameLimit;
    Point2D offset;

    CameraShake(int limit, Point2D off) {
        frameLimit = limit;
        offset = off;
    }
};

}  // namespace ECSEngine
