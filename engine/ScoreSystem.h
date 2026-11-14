#pragma once

#include <vector>

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
        for (const auto& entity : entManager) {
            EntityID id = entity.GetID();

            if (!entManager.template HasComponent<ScoreComponent>(id)) {
                continue;
            }

            ScoreComponent& score = entManager.template GetComponent<ScoreComponent>(id);
            int actualScore = score.score;
            int hundos = (actualScore / 100) % 10;
            int dozens = (actualScore / 10) % 10;
            int onses = actualScore % 10;

            std::vector<int> digits = {hundos, dozens, onses};

            for (int i = 0; i < 3; i++) {
                EntityID id2 = score.digitID[i];

                if (!entManager.template HasComponent<SpriteComponent>(id2)) {
                    continue;
                }
                SpriteComponent& sprite = entManager.template GetComponent<SpriteComponent>(id2);
                sprite.textureID = score.digitTextureID[digits[i]];
            }
        }
        return kContinue;
    }
};

}  // namespace ECSEngine
