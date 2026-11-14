#pragma once

#include <algorithm>
#include <string>

#include "CollisionComponent.h"
#include "LocationComponent.h"
#include "SoundManager.h"
#include "SystemManager.h"

namespace ECSEngine {

template <typename... Components>
class CollisionLateSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("CollisionLateSystem");
        return name;
    }

    tSystemReturn Run(EngineView<Components...>* engine) override {
        auto& entityManager = engine->GetEntityManager();
        for (const auto& entity : entityManager) {
            EntityID id = entity.GetID();

            if (!entityManager.template HasComponent<CollisionComponent>(id) || !entityManager.template HasComponent<LocationComponent>(id)) {
                continue;
            }
            auto& collision = entityManager.template GetComponent<CollisionComponent>(id);
            auto& location = entityManager.template GetComponent<LocationComponent>(id);

            collision.previousCollisionBox = collision.collisionBox;
            collision.previousCollisionBox.topLeft.x += location.loc.x;
            collision.previousCollisionBox.topLeft.y += location.loc.y;
        }
        return kContinue;
    }
};

}  // namespace ECSEngine
