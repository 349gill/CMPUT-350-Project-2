#pragma once

#include <random>

#include "Entity.h"
#include "SpawnComponent.h"
namespace ECSEngine {

template <typename... Components>
class SpawnSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("SpawnSystem");
        return name;
    }

    tSystemReturn Run(EngineView<Components...>* engine) override {
        auto& entManager = engine->GetEntityManager();
        static std::mt19937 gen(std::random_device{}());
        std::uniform_real_distribution<float> speed(-5.f, 5.f);

        // index loop: creating entities below would invalidate iterators
        EntityID count = static_cast<EntityID>(entManager.end() - entManager.begin());
        for (EntityID id = 0; id < count; ++id) {
            if (!entManager.template HasComponent<SpawnComponent>(id) || !entManager.template HasComponent<LocationComponent>(id)) {
                continue;
            }

            SpawnComponent& spawn = entManager.template GetComponent<SpawnComponent>(id);

            if (spawn.totalSpawns <= 0) {
                continue;
            }
            if (spawn.timeToNextSpawn > 0) {
                spawn.timeToNextSpawn -= 1;
            }
            if (spawn.timeToNextSpawn == 0) {
                spawn.timeToNextSpawn = spawn.timeBetweenSpawns;
                spawn.totalSpawns -= 1;
                SpriteID texture = spawn.spawnTextureID;
                Point2D spawnLoc = entManager.template GetComponent<LocationComponent>(id).loc;
                spawnLoc.y += 64.f;  // just below the spawner tile

                EntityID newStar = entManager.CreateEntity("star");

                entManager.template AddComponent<LocationComponent>(newStar, LocationComponent(spawnLoc));
                entManager.template AddComponent<MovementComponent>(newStar, MovementComponent(speed(gen), speed(gen)));
                entManager.template AddComponent<SpriteComponent>(newStar, SpriteComponent(texture, Rect{{0.f, 0.f}, 32.f, 32.f}, true));
                CollisionComponent collision;
                collision.staticEntity = 0;
                collision.collisionBox = {{0.f, 0.f}, 32.f, 32.f};

                entManager.template AddComponent<CollisionComponent>(newStar, collision);
            }
        }
        return kContinue;
    }
};

}  // namespace ECSEngine
