#pragma once

#include <algorithm>
#include <string>

#include "CollisionComponent.h"
#include "InputComponent.h"
#include "LocationComponent.h"
#include "ScoreComponent.h"
#include "SoundManager.h"
#include "SystemManager.h"

namespace ECSEngine {

template <typename... Components>
class CollisionSystem : public System<Components...> {
public:
    const std::string& GetName() const override {
        static std::string name("CollisionSystem");
        return name;
    }

    tSystemReturn Run(EngineView<Components...>* engine) override {
        auto& entManager = engine->GetEntityManager();

        for (const auto& entity : entManager) {
            EntityID id = entity.GetID();

            if (!entManager.template HasComponent<CollisionComponent>(id) || !entManager.template HasComponent<LocationComponent>(id) ||
                !entManager.template HasComponent<MovementComponent>(id)) {
                continue;
            }

            CollisionComponent& boxA = entManager.template GetComponent<CollisionComponent>(id);
            if (boxA.staticEntity) {
                continue;
            }
            bool wasOnGround = boxA.onGround;
            boxA.onCeiling = false;
            boxA.onGround = false;
            boxA.onLeftWall = false;
            boxA.onRightWall = false;

            LocationComponent& locA = entManager.template GetComponent<LocationComponent>(id);
            MovementComponent& moveA = entManager.template GetComponent<MovementComponent>(id);
            bool isPlayer = entManager.template HasComponent<InputComponent>(id);
            float rest = isPlayer ? 0.f : -0.8f;  // stars bounce and lose speed

            for (const auto& other : entManager) {
                EntityID id2 = other.GetID();

                if (id == id2 || !entManager.template HasComponent<CollisionComponent>(id2) || !entManager.template HasComponent<LocationComponent>(id2)) {
                    continue;
                }

                CollisionComponent& boxB = entManager.template GetComponent<CollisionComponent>(id2);
                LocationComponent& locB = entManager.template GetComponent<LocationComponent>(id2);

                Rect rectA = boxA.collisionBox;
                Rect rectB = boxB.collisionBox;

                rectA.topLeft.x += locA.loc.x;
                rectA.topLeft.y += locA.loc.y;

                rectB.topLeft.x += locB.loc.x;
                rectB.topLeft.y += locB.loc.y;

                float aLeft = rectA.topLeft.x;
                float aRight = aLeft + rectA.width;
                float aTop = rectA.topLeft.y;
                float aBottom = aTop + rectA.height;

                float bLeft = rectB.topLeft.x;
                float bRight = bLeft + rectB.width;
                float bTop = rectB.topLeft.y;
                float bBottom = bTop + rectB.height;

                if (!(aLeft < bRight && aRight > bLeft && aTop < bBottom && aBottom > bTop)) {
                    continue;
                }

                float overX = std::min(aRight, bRight) - std::max(aLeft, bLeft);
                float overY = std::min(aBottom, bBottom) - std::max(aTop, bTop);

                if (boxB.doesDamage && entManager.template HasComponent<RespawnComponent>(id)) {
                    locA.loc = entManager.template GetComponent<RespawnComponent>(id).loc;
                    moveA.velocity = Point2D(0.f, 0.f);
                    break;
                }

                if (boxB.staticEntity) {
                    // Use the previous frame's box to decide which side was hit
                    enum Side { LEFT, RIGHT, UP, DOWN };
                    Side side;
                    const Rect& pA = boxA.previousCollisionBox;
                    if (pA.topLeft.y < bBottom && pA.topLeft.y + pA.height > bTop) {
                        side = (pA.topLeft.x < bLeft) ? RIGHT : LEFT;
                    }
                    else {
                        side = (pA.topLeft.y < bTop) ? UP : DOWN;
                    }

                    switch (side) {
                        case DOWN:
                            locA.loc.y += overY;
                            moveA.velocity.y *= rest;
                            boxA.onCeiling = true;
                            break;
                        case UP:
                            locA.loc.y -= overY;
                            moveA.velocity.y *= rest;
                            boxA.onGround = true;
                            if (isPlayer && !wasOnGround) {
                                engine->GetSoundManager().GetSound("land").play();
                            }
                            break;
                        case RIGHT:
                            locA.loc.x -= overX;
                            moveA.velocity.x *= rest;
                            boxA.onRightWall = true;
                            break;
                        case LEFT:
                            locA.loc.x += overX;
                            moveA.velocity.x *= rest;
                            boxA.onLeftWall = true;
                            break;
                    }
                }
                else if (entManager.template HasComponent<InputComponent>(id2)) {
                    continue;  // handled when the player is "A"
                }
                else if (isPlayer) {
                    // player collects dynamic item
                    entManager.RemoveEntity(id2);
                    engine->GetSoundManager().GetSound("star").play();
                    for (const auto& e : entManager) {
                        if (entManager.template HasComponent<ScoreComponent>(e.GetID())) {
                            entManager.template GetComponent<ScoreComponent>(e.GetID()).score++;
                        }
                    }
                }
                else {
                    // both dynamic: each side moves itself half the overlap on its own pass
                    if (overX < overY) {
                        locA.loc.x += (aLeft < bLeft ? -overX : overX) / 2.f;
                    }
                    else {
                        locA.loc.y += (aTop < bTop ? -overY : overY) / 2.f;
                    }
                }
            }
        }

        return kContinue;
    }
    };
}  // namespace ECSEngine
