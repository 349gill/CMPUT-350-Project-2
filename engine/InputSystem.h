#pragma once

#include "CollisionComponent.h"
#include "InputComponent.h"
#include "LocationComponent.h"
#include "SoundManager.h"
#include "SystemManager.h"
#include "Entity.h"
#include "Keyboard.h"
#include <algorithm>

namespace ECSEngine {

const float kMaxRunVelocity = 15;
const float kDashVelocity = 50;
const float kJumpVelocity = 25;
const float kGroundRunAcceleration = 5;
const float kAirRunAcceleration = 4;
const int kDashInterval = 60;
const int kDashFrames = 10;

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

            if (!entManager.template HasComponent<InputComponent>(id) || !entManager.template HasComponent<MovementComponent>(id)) {
                continue;
            }
            InputComponent& input = entManager.template GetComponent<InputComponent>(id);
            MovementComponent& move = entManager.template GetComponent<MovementComponent>(id);
            CollisionComponent& box = entManager.template GetComponent<CollisionComponent>(id);
            
            bool lP = input.keydown.test(Key::Left);
            bool rP = input.keydown.test(Key::Right);
            bool dP = input.keydown.test(Key::Down);
            bool jP = input.keydown.test(Key::Z) && !input.lastKeydown.test(Key::Z);
            bool cP = input.keydown.test(Key::C);
            bool jumpReleased = !input.keydown.test(Key::Z) && input.lastKeydown.test(Key::Z);

            float acceleration = box.onGround ? kGroundRunAcceleration : kAirRunAcceleration;

            input.lastDash += 1;

            if (input.lastDash >= kDashFrames) {  // no steering while dashing
                if (lP && !rP) {
                    move.velocity.x -= acceleration;
                }
                else if (rP && !lP) {
                    move.velocity.x += acceleration;
                }
                else {
                    float resist = 3.f;
                    if (move.velocity.x > 0.f) {
                        move.velocity.x = std::max(0.f, move.velocity.x - resist);
                    }
                    else if (move.velocity.x < 0.f) {
                        move.velocity.x = std::min(0.f, move.velocity.x + resist);
                    }
                }
                move.velocity.x = std::clamp(move.velocity.x, -kMaxRunVelocity, kMaxRunVelocity);
            }

            // Jumps
            if (jP) {
                bool jumped = true;
                if (box.onGround) {
                    move.velocity.y = -kJumpVelocity;
                }
                else if (box.onLeftWall && lP && move.velocity.y > 0.f) {
                    move.velocity.x = kMaxRunVelocity;
                    move.velocity.y = -kJumpVelocity;
                }
                else if (box.onRightWall && rP && move.velocity.y > 0.f) {
                    move.velocity.x = -kMaxRunVelocity;
                    move.velocity.y = -kJumpVelocity;
                }
                else {
                    jumped = false;
                }
                if (jumped) {
                    engine->GetSoundManager().GetSound("jump").play();
                }
            }

            if (jumpReleased && move.velocity.y < 0.f) {
                move.velocity.y *= 0.5f;
            }

            // Dash (once per second)
            if (cP && input.lastDash >= kDashInterval && lP != rP) {
                move.velocity.x = lP ? -kDashVelocity : kDashVelocity;
                move.velocity.y = 0.f;
                if (entManager.template HasComponent<GravityComponent>(id)) {
                    entManager.template GetComponent<GravityComponent>(id).disabledTimer = kDashFrames;
                }
                input.lastDash = 0;
            }

            // fast fall
            if (dP && !box.onGround && move.velocity.y > 0.f) {
                move.velocity.y += 1.f;
            }

            input.lastKeydown = input.keydown;
        }
        return kContinue; 
    }
};

}  // namespace ECSEngine
