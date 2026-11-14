#pragma once

#include "Entity.h"
#include "Keyboard.h"
#include <algorithm>

namespace ECSEngine {

const float kMaxRunVelocity = 15;
const float kDashVelocity = 50;
const float kJumpVelocity = 25;
const float kGroundRunAcceleration = 5;
const float kAirRunAcceleration = 4;
const float kDashInterval = 25;

template <typename... Components>
class InputSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("InputSystem");
        return name;
    }

    tSystemReturn Run(EngineView<Components...>* engine) override { 
        auto& entManager = engine->GetEntityManager();
        for (const auto& entity: entManager) {
            EntityID id = entity.GetID();

            if (!entManager.HasComponent<InputComponent>(id) || !entManager.HasComponent<MovementComponent>(id)) {
                continue;
            }
            InputComponent& input = entManager.GetComponent<InputComponent>(id);
            MovementComponent& move = entManager.GetComponent<MovementComponent>(id);
            CollisionComponent& box = entManager.GetComponent<CollisionComponent>(id);

            bool lP = input.keydown.test(Key::Left);
            bool rP = input.keydown.test(Key::Right);
            bool dP = input.keydown.test(Key::Down);
            bool jP = input.keydown.test(Key::Z) && !input.lastKeydown.test(Key::Z);
            bool cP = input.keydown.test(Key::C);

            bool jPP = input.keydown.test(Key::Z) && !input.lastKeydown.test(Key::Z);
            bool cPP = input.keydown.test(Key::C) && !input.lastKeydown.test(Key::C);

            bool jumpReleased =!input.keydown.test(Key::Z) &&input.lastKeydown.test(Key::Z);
            
            float acceleration = box.onGround? kGroundRunAcceleration: kAirRunAcceleration;

            input.lastDash += 1.f;

            // horizontal movememnet
            if (lP && !rP) {
                    move.velocity.x -= acceleration;
                }
            else if (rP && !lP) {
                    move.velocity.x += acceleration;
                }
            else {
                    // Decelerate when no direction is held.
                    float resist = 3.f;

                    if (move.velocity.x > 0.f) {
                        move.velocity.x = std::max(0.f, move.velocity.x - resist);
                    }
                    else if (move.velocity.x < 0.f) {
                        move.velocity.x = std::min(0.f, move.velocity.x + resist);
                    }

                move.velocity.x = std::clamp(move.velocity.x, -kMaxRunVelocity,kMaxRunVelocity);
                }
            
            // Jumps
            if (jP) {
                if (box.onGround) {
                    move.velocity.y = -kJumpVelocity;
                }
                else if (box.onLeftWall && lP && move.velocity.y > 0.f) {
                    move.velocity.x = kAirRunAcceleration;
                    move.velocity.y = -kJumpVelocity;
                }
                else if (box.onRightWall && rP && move.velocity.y > 0.f) {
                    move.velocity.x = -kAirRunAcceleration;
                    move.velocity.y = -kJumpVelocity;
                }
            }

            if (jumpReleased && move.velocity.y < 0.f) {
                move.velocity.y *= 0.5f;
            }

            // Dash
            if (cP && input.lastDash >= kDashInterval) {
                bool dashed = false;

                if (lP && !rP) {
                    move.velocity.x = -kDashVelocity;
                    dashed = true;
                }
                else if (rP && !lP) {
                    move.velocity.x = kDashVelocity;
                    dashed = true;
                }

                if (dashed) {
                    input.lastDash = 0;
                }
            }

            // fast fall
            if (dP && !box.onGround && move.velocity.y > 0.f) {
                move.velocity.y += -9.81;
            }

            input.lastKeydown = input.keydown;
        }
        return kContinue; 
    }
};

}  // namespace ECSEngine
