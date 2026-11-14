#pragma once

#include "ScoreComponent.h"
namespace ECSEngine {

template <typename... Components>
class ScoreSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("ScoreSystem");
        return name;
    }

    tSystemReturn Run(EngineView<Components...>* engine) override { 
        auto& entManager = engine->GetEntityManager();
        for (const auto& entity: entManager) {
            EntityID id = entity.GetID();

            if (!entManager.HasComponent<ScoreComponent>(id)) {
                continue;
            }

            ScoreComponent& score = entManager.GetComponent<MovementComponent>(id);
            int actualScore = score.score;
            int hundos = (actualScore / 100) % 10;
            int dozens = (actualScore / 10) % 10;
            int onses = actualScore % 10;

            int std::vector<int> digits = {onses, dozens, hundos};
            
            for (int i = 0; i < 2; i++) {
                entityID id2 = score.digitID[i];

                if (id2 == NULL) {
                    continue;
                }
                if (!entManager.HasComponent<SpriteComponent>(id2)) {
                    continue;
                }
                SpriteComponent sprite = entManager.GETComponent<SpriteComponent>(id2);
                sprite.textureID = scoreComponent.digitTextureID[digits[i]];

                
            }

        return kContinue;
     }
};

}  // namespace ECSEngine
