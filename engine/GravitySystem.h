#pragma once

#include <algorithm>
#include <string>

#include "CollisionComponent.h"
#include "LocationComponent.h"
#include "SoundManager.h"
#include "SystemManager.h"

namespace ECSEngine
{

template <typename... Components>
class GravitySystem : public System<Components...> {
public:
	const std::string & GetName() const override
	{ static std::string name("GravitySystem"); return name; }
	
	tSystemReturn Run(EngineView<Components...> *engine) override
	{
		auto& entManager = engine->GetEntityManager();
        for (const auto& entity: entManager) {
            EntityID id = entity.GetID();

            if (!entManager.template HasComponent<GravityComponent>(id) || !entManager.template HasComponent<MovementComponent>(id) || !entManager.template HasComponent<CollisionComponent>(id)) {
                continue;
            }

			GravityComponent& gravity = entManager.template GetComponent<GravityComponent>(id);
			MovementComponent& move = entManager.template GetComponent<MovementComponent>(id);
			CollisionComponent& box = entManager.template GetComponent<CollisionComponent>(id);

			if (gravity.disabledTimer == 0) {
				move.velocity.y += gravity.acceleration.y * (move.velocity.y > 0.f ? 1.5f : 1.f);
				move.velocity.y = std::min(move.velocity.y, 30.f);

				if (!box.onGround && (box.onLeftWall || box.onRightWall) && move.velocity.y > 3.f) {
					move.velocity.y = 3.f;
					auto& wall = engine->GetSoundManager().GetSound("wall");
					if (wall.getStatus() != sf::Sound::Status::Playing) {
						wall.play();
					}
				}
			}
			else {
				gravity.disabledTimer -= 1;
}


		}
		return kContinue;
	}
	
};


}



