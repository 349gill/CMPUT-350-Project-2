#pragma once

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

            if (!entManager.HasComponent<GravityComponent>(id) || !entManager.HasComponent<MovementComponent>(id) || !entManager.HasComponent<CollisionComponent>(id)) {
                continue;
            }

			GravityComponent& gravity = entManager.GetComponent<GravityComponent>(id);
			MovementComponent& move = entManager.GetComponent<MovementComponent>(id);
			CollisionComponent& box = entManager.GetComponent<CollisionComponent>(id);

			if (gravity.disabledTimer == 0) {
				if (box.onGround ) {
					if (move.velocity.y > 0) {
						move.velocity.y = 0.f;
					}
					
				}
				else {
					move.velocity.y += gravity.acceleration.y;
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



