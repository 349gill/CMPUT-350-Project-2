#pragma once

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
        for (const Entity& entity : entManager) {
        EntityID id = entity.GetID();

        if (!entManager.HasComponent<SpawnComponent>(id)) {
            continue;
        }

        SpawnComponent& spawn = entManager.GetComponent<SpawnComponent>(id);

        if (spawn.totalSpawns <= 0) {
            continue;
        }
        if (spawn.timeToNextSpawn > 0) {
            spawn.timeToNextSpawn -= 1;
        }
        if (spawn.timeToNextSpawn == 0) {
            EntityID newStar = entManager.CreateEntity("star");

            entManager.AddComponent<LocationComponent>(newStar, LocationComponent(100.f, 200.f));
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<float> speedX(-5.f, 5.f);
            std::uniform_int_distribution<float> speedY(-5.f, 5.f);
            entManager.AddComponent<MovementComponent>(newStar, MovementComponent(speedX, speedY));
            entManager.AddComponent<SpriteComponent>(newStar,SpriteComponent(spawn.spawnTextureID,{{0.f, 0.f}, 32.f, 32.f},true);
            CollisionComponent collision;
            collision.staticEntity = 0;
            collision.collisionBox = {{0.f, 0.f}, 32.f, 32.f};

            entManager.AddComponent<CollisionComponent>(newStar, collision);

        }
    } 
        return kContinue; 
    }
};

}  // namespace ECSEngine
