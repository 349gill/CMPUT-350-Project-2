#pragma once

#include <unordered_map>

#include "LocationComponent.h"
#include "MathUtil.h"
#include "SpriteComponent.h"
#include "SystemManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ECSEngine {

template <typename... Components>
class CameraSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name = "CameraSystem";
        return name;
    }

    tSystemReturn Run(EngineView<Components...>* engine) override { 
        auto& entManager = engine->GetEntityManager();
        auto& window = engine->GetWindowManager();
        float width = static_cast<float>(window.GetWindow()->getSize().x);


        for (const auto& entity: entManager) {
            EntityID id = entity.GetID();

            if (!entManager.HasComponent<CameraComponent>(id) || !entManager.HasComponent<CameraFollower>(id)) {
                continue;
            }

            CameraComponent& camera = entManager.GetComponent<CameraComponent>(id);
            CameraFollower& follower = entManager.GetComponent<CameraFollower>(id);
            EntityID targetID = follower.entityID;

            if (!entManager.HasComponent<LocationComponent>(targetID)) {
                continue;
            }

            LocationComponent& player = entManager.GetComponent<LocationComponent>(targetID);
            float scale = camera.worldUnitsPerPixel;

            // horizontal screen pos
            float playerX = width / 2.f + (player.loc.x - camera.position.x) / scale;

            float leftHard = width * 0.1f;
            float rightHard = width * 0.9f;

            float leftSoft = width * 0.3f;
            float rightSoft = width * 0.7f;

            if (playerX < leftHard) {
                camera.position.x -= (leftHard - playerX) * scale;
            }
            else if (playerX > rightHard) {
                camera.position.x += (playerX - rightHard) * scale;
            }


            playerX = width / 2.f + (player.loc.x - camera.position.x) / scale;

            float speed = std::clamp(camera.speed, 0.f, 1.f);

            if (playerX < leftSoft) {
                camera.position.x -= (leftSoft - playerX) * scale * speed;
            }
            else if (playerX > rightSoft) {
                camera.position.x += (playerX - rightSoft) * scale * speed;
            }

            window.SetWorldCenter(camera.position);
            window.SetWorldScale(scale);

        return kContinue; 
    }
};

}  // namespace ECSEngine
