#pragma once

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
        for (const auto entity: entityManager) {
            EntityID id = entity.GetID();

            if (!entityManager.HasComponent<CollisionComponent>(id) || !entityManager.HasComponent<LocationComponent>(id)) {
                continue;
            }
            auto& collision = entityManager.GetComponent<CollisionComponent>(id);
            auto& location = entityManager.GetComponeny<LocationComponent>(id);

            collision.previousCollisionBox = collision.collisionBox;

            collision.previousCollisionBox.topLeft.x += location.loc.x;
            collision.previousCollisionBox.topLeft.y += location.loc.y;
        }

     }
     return kContinue;
};

}  // namespace ECSEngine
