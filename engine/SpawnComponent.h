#pragma once

#include <unordered_map>

#include "MathUtil.h"
#include <string.h>
#include "SpriteManager.h"

namespace ECSEngine {

// The sprite rectangle is relative to the entity location in the world
// This is only defined if an entity also has a LocationComponent.
class SpawnComponent {
public:
    EntityID entityID;  // The entity that this spawn component is attached to
    std::string spawnType;
    SpriteID spawnTextureID;
    int timeToNextSpawn;
    int timeBetweenSpawns;  // in frames
    int totalSpawns;
    SpawnComponent(EntityID id, std::string type, SpriteID spawnID, int timeNext, int timeBet, int total) {
        entityID = id;
        spawnType = type;
        spawnTextureID = spawnID;
        timeToNextSpawn = timeNext;
        timeBetweenSpawns = timeBet;
        totalSpawns = total;
    }

private:
};

}  // namespace ECSEngine
