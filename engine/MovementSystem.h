#pragma once

namespace ECSEngine {

template <typename... Components>
class MovementSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("MovementSystem");
        return name;
    }

    tSystemReturn Run(EngineView<Components...>* engine) override { 
        auto& entManager = engine->GetEntityManager();
        for (const auto& entity: entManager) {
            EntityID id = entity.GetID();

            if (!entManager.HasComponent<MovementComponent>(id) || !entManager.HasComponent<LocationComponent>(id)) {
                continue;
            }

            MovementComponent& move = entManager.GetComponent<MovementComponent>(id);
            LocationComponent& loc = entManager.GetComponent<LocationComponent>(id);

            loc.loc.x += move.velocity.x;
            loc.loc.y += move.velocity.y;


        }
        return kContinue; 
    }
};

}  // namespace ECSEngine
