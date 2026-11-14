#pragma once

#include <bitset>
#include <unordered_map>

#include "CameraComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include "MathUtil.h"
#include "SpriteManager.h"
#include "SystemManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ECSEngine {

template <typename... Components>
class SpriteSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("SpriteSystem");
        return name;
    }

    tSystemReturn Run(EngineView<Components...>* engine) override { 
        auto& entManager = engine->GetEntityManager();
        SpriteManager& spriteManager = engine->GetSpriteManager();
        auto& windowManager = engine->GetWindowManager();

        std::shared_ptr<sf::RenderWindow> window = windowManager.GetWindow();

        for (const Entity& entity: entManager) {
            EntityID id = entity.GetID();
            if (!entManager.HasComponent<SpriteComponent>(id)) {
                continue;
            }

            SpriteComponent& spriteComp = entManager.GetComponent<SpriteComponent>(id);

            Rect bounds = spriteComp.bounds;

            if (spriteComp.worldSpace) {
                if (!entManager.HasComponent<LocationComponent>(id)) {
                    continue;
                }

                LocationComponent& loc = entManager.GetComponent<LocationComponent>(id);

                bounds.topLeft.x += loc.loc.x;
                bounds.topLeft.y += loc.loc.y;

                bounds = windowManager.WorldToWindow(bounds);

            }

            sf::Sprite& sprite = spriteManager.GetSprite(spriteComp.textureID);
            sprite.setPosition(bounds.topLeft.x, bounds.topLeft.y);

            sf::Vector2f sizo = sprite.getLocalBounds().size;

            if (sizo.x > 0.f && sizo.y > 0.f) {
                sprite.setScale({bounds.width / sizo.x, bounds.height / sizo.y});
            }

            window->draw(sprite);
        }


        return kContinue; 
    }
};

}  // namespace ECSEngine
