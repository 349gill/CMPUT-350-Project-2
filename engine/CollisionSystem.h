#pragma once

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

            if (!entManager.HasComponent<CollisionComponent>(id) || !entManager.HasComponent<LocationComponent>(id)) {
                continue;
            }

            CollisionComponent& boxA = entManager.GetComponent<CollisionComponent>(id);

            boxA.onCeiling = false;
            boxA.onGround = false;
            boxA.onLeftWall = false;
            boxA.onRightWall = false;

            LocationComponent& locA = entManager.GetComponent<LocationComponent>(id);
            MovementComponent& moveA = entManager.GetComponent<MovementComponent>(id);

            for (const auto& entity : entManager) {
                EntityID id2 = entity.GetID();

                if (!entManager.HasComponent<CollisionComponent>(id2) || !entManager.HasComponent<LocationComponent>(id2) || id == id2) {
                    continue;
                }
                
                CollisionComponent& boxB = entManager.GetComponent<CollisionComponent>(id2);

                LocationComponent& locB = entManager.GetComponent<LocationComponent>(id2);

                MovementComponent& moveB = entManager.GetComponent<MovementComponent>(id2);


                

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

                bool overlapX = aLeft < bRight && aRight > bLeft;
                bool overlapY = aTop < bBottom && aBottom > bTop;

                if (overlapX && overlapY) {
                    float overX = std::min(aRight, bRight) - std::max(aLeft, bLeft);
                    float overY = std::min(aBottom, bBottom) - std::max(aTop, bTop); 

                    enum side  {LEFT, RIGHT, UP, DOWN};
                    // determine where collieds
                    CollisionComponent prevA = boxA.previousCollisionBox;
                    if (prevA.collisionBox.topLeft.y + prevA.collisionBox.height <= bTop){
                        side colType = UP;
                    }
                    else if (prevA.collisionBox.topLeft.y >= bBottom){
                        side colType = DOWN;
                    }
                    else if (prevA.collisionBox.topLeft.x + prevA.collisionBox.width <= bLeft){
                        side colType = RIGHT;
                    }
                    else if (prevA.collisionBox.topLeft.x >= bRight){
                        side colType = LEFT;
                    }

                    // if A is dynamic and B static
                    if (!boxA.staticEntity && boxB.staticEntity) {
                        switch (side) {
                            case DOWN {
                                locA.loc.y += overY;
                                moveA.velocity.y = 0.f;
                                boxA.onCeiling = true;
                            },
                            case UP {
                                locA.loc.y -= overY;
                                moveA.velocity.y = 0.f;
                                boxA.onGround = true;
                            },
                            case RIGHT {
                                locA.loc.x -= overX;
                                moveA.velocity.x = 0.f;
                                boxA.onRightWall = true;
                            },
                            case LEFT {
                                locA.loc.x += overX;
                                moveA.velocity.x = 0.f;
                                boxA.onLeftWall = true;
                            },

                        }
                    }
                    else if (boxA.staticEntity && boxB.staticEntity){
                        switch (side) {
                            case DOWN {
                                locB.loc.y -= overY;
                                moveB.velocity.y = 0.f;
                                boxB.onCeiling = true;
                            },
                            case UP {
                                locB.loc.y += overY;
                                moveB.velocity.y = 0.f;
                                boxB.onGround = true;
                            },
                            case RIGHT {
                                locB.loc.x += overX;
                                moveB.velocity.x = 0.f;
                                boxB.onLeftWall = true;
                            },
                            case LEFT {
                                locB.loc.x -= overX;
                                moveB.velocity.x = 0.f
                                boxB.onRightWall = true;
                            },
                    }
                    // both dynamic so cooked
                    else {
                        // check if horzontal
                        if (overX > overY) {
                            if (locB.loc.x <= locA.loc.x) {
                                locB.loc.x -= overX / 2.f;
                                locA.loc.x += overX / 2.f;
                            }
                            else {
                                locB.loc.x += overX / 2.f;
                                locA.loc.x -= overX / 2.f;
                            }
                        }
                        else {
                            if (locB.loc.y <= locA.loc.y) {
                                locB.loc.y -= overY / 2.f;
                                locA.loc.y += overY / 2.f;
                            }
                            else {
                                locB.loc.y += overY / 2.f;
                                locA.loc.y -= overY / 2.f;
                            }
                        }
                    }
                }

                
                

            }
        }

        return kContinue; 
    }
};

}  // namespace ECSEngine
