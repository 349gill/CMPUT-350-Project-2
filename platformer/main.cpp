#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "CameraSystem.h"
#include "CollisionComponent.h"
#include "CollisionLateSystem.h"
#include "CollisionSystem.h"
#include "ECSEngine.h"
#include "EntityManager.h"
#include "GravitySystem.h"
#include "InputComponent.h"
#include "InputSystem.h"
#include "LocationComponent.h"
#include "MathUtil.h"
#include "MovementSystem.h"
#include "ScoreComponent.h"
#include "ScoreSystem.h"
#include "SpawnComponent.h"
#include "SpawnSystem.h"
#include "SpriteComponent.h"
#include "SpriteManager.h"
#include "SpriteSystem.h"

std::string gResourcePath = "../../assets/";
#define COMPONENTS                                                                             \
    ECSEngine::LocationComponent, ECSEngine::MovementComponent, ECSEngine::CollisionComponent, \
        ECSEngine::SpriteComponent, ECSEngine::SpawnComponent, ECSEngine::CameraComponent,     \
        ECSEngine::CameraFollower, ECSEngine::InputComponent, ECSEngine::GravityComponent,     \
        ECSEngine::CameraShake, ECSEngine::ScoreComponent, ECSEngine::RespawnComponent
using Engine = ECSEngine::ECSEngine<COMPONENTS>;

using ECSEngine::EntityID;
using ECSEngine::Point2D;
using ECSEngine::Rect;
using ECSEngine::SpriteID;

const std::string kPlayerSheet = "player.png";
const Rect kPlayerSource = {{0.0f, 0.0f}, 0, 0}; // 0 size = use the whole image
const Rect kPlayerBounds = {{0.0f, 0.0f}, 48, 64}; // Player sprite bounds
const Rect kPlayerCollision = {{6.0f, 4.0f}, 36, 60}; // Player collision box
const Point2D kPlayerStart(800.0f, 500.0f);
const float kGravity = 1.0f;

const std::string kStarSheet = "star.png";
const Rect kStarSource = {{0.0f, 0.0f}, 0, 0}; // 0 size = use the whole image
const Rect kStarBounds = {{0.0f, 0.0f}, 48, 48}; // Star sprite bounds

const char kSpikeChar = 'x';
const char kSpawnerChar = 'S';
const int kSpawnPeriod = 120; // 120 frames (2 seconds)
const int kSpawnCount = 30;

SpriteID gStarSprite = 0;

ECSEngine::CollisionComponent MakeCollision(
    const Point2D& loc, 
    const Rect& box, 
    bool isStatic,
    bool damage) {
    ECSEngine::CollisionComponent c{};
    c.staticEntity = isStatic;
    c.doesDamage = damage;
    c.collisionBox = box;
    c.previousCollisionBox = Rect{{loc.x + box.topLeft.x, loc.y + box.topLeft.y}, box.width, box.height};

    return c;
}

void LoadMap(Engine& engine, const std::string& path, const std::string& file) {
    std::ifstream in(path + file);
    if (!in) {
        std::cout << "Could not open map: " << path + file << "\n";
        return;
    }

    auto& em = engine.GetEntityManager();

    struct Tile {
        SpriteID sprite;
        Rect box;
    };
    std::unordered_map<char, Tile> dictionary;

    std::string token;
    int type;
    in >> token >> type;
    while (in >> token && token != "map") {
        std::string sheet;
        float x, y, w, h;
        in >> sheet >> x >> y >> w >> h;
        Tile tile;
        tile.sprite = engine.GetSpriteManager().RegisterTexture(path + sheet, Rect{{x, y}, w, h});
        tile.box = Rect{{0.0f, 0.0f}, 0.0f, 0.0f};
        if (type == 2) {
            in >> x >> y >> w >> h;
            tile.box = Rect{{x, y}, w, h};
        }
        dictionary[token[0]] = tile;
    }

    float originX, originY, tileW, tileH;
    int gridW, gridH;
    in >> token >> originX >> originY >> token >> tileW >> tileH >> token >> gridW >> gridH;

    // One entity per tile
    for (int row = 0; row < gridH; row++) {
        std::string line;
        in >> line;
        for (int col = 0; col < gridW && col < static_cast<int>(line.size()); col++) {
            auto it = dictionary.find(line[col]);
            if (it == dictionary.end()) continue;

            Point2D loc(originX + col * tileW, originY + row * tileH);
            EntityID id = em.CreateEntity("tile");
            em.AddComponent(id, ECSEngine::LocationComponent{loc});
            em.AddComponent(id, ECSEngine::SpriteComponent{
                                    it->second.sprite, Rect{{0.0f, 0.0f}, tileW, tileH}, true});
            if (type != 2) continue;

            em.AddComponent(id, MakeCollision(loc, it->second.box, true, line[col] == kSpikeChar));
            if (line[col] == kSpawnerChar) {
                em.AddComponent(id, ECSEngine::SpawnComponent
                    {id, "star", gStarSprite, kSpawnPeriod, kSpawnPeriod, kSpawnCount});
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc >= 3 && argv[1] == std::string("-path")) {
        gResourcePath = argv[2];
    }
    std::cout << "Usage: " << argv[0] << " [-path resource_path]\n";
    std::cout << "Using resource path: " << gResourcePath << "\n";

    // Engine test code
    Engine engine(1024, 768, "Test Engine");

    auto& em = engine.GetEntityManager();
    auto& sprites = engine.GetSpriteManager();

    // Load sounds
    auto& sounds = engine.GetSoundManager();
    sounds.RegisterSound(gResourcePath + "sfx_jump.ogg", "jump");
    sounds.RegisterSound(gResourcePath + "sfx_bump.ogg", "land");
    sounds.RegisterSound(gResourcePath + "sfx_coin.ogg", "star");
    sounds.RegisterSound(gResourcePath + "sfx_bump.ogg", "wall");

    // Load maps
    gStarSprite = sprites.RegisterTexture(gResourcePath + kStarSheet, kStarSource);
    LoadMap(engine, gResourcePath, "sky.map");
    LoadMap(engine, gResourcePath, "world.map");

    Point2D starLoc(400.0f, 300.0f);
    EntityID star = em.CreateEntity("star");
    em.AddComponent(star, ECSEngine::LocationComponent{starLoc});
    em.AddComponent(star, ECSEngine::SpriteComponent{gStarSprite, kStarBounds, true});
    em.AddComponent(star, MakeCollision(starLoc, kStarBounds, false, false));

    // Place player
    SpriteID playerSprite = sprites.RegisterTexture(gResourcePath + kPlayerSheet, kPlayerSource);
    EntityID player = em.CreateEntity("player");
    em.AddComponent(player, ECSEngine::LocationComponent{kPlayerStart});
    em.AddComponent(player, ECSEngine::MovementComponent{Point2D(0.0f, 0.0f)});
    em.AddComponent(player, ECSEngine::GravityComponent(Point2D(0.0f, kGravity)));
    em.AddComponent(player, ECSEngine::InputComponent(player));
    em.AddComponent(player, ECSEngine::RespawnComponent{kPlayerStart});
    em.AddComponent(player, ECSEngine::SpriteComponent{playerSprite, kPlayerBounds, true});
    em.AddComponent(player, MakeCollision(kPlayerStart, kPlayerCollision, false, false));

    // Setup score component: three digits drawn in screen space
    ECSEngine::ScoreComponent score;
    score.score = 0;
    for (int i = 0; i < 10; i++) {
        score.digitTextureID[i] = sprites.RegisterTexture(
            gResourcePath + "hud_character_" + std::to_string(i) + ".png", Rect{{0.0f, 0.0f}, 0, 0});
    }

    for (int i = 0; i < 3; i++) {
        score.digitID[i] = em.CreateEntity("digit");
        ECSEngine::LocationComponent location = ECSEngine::LocationComponent{Point2D(10.0f + i * 40.0f, 10.0f)};
        ECSEngine::SpriteComponent sprite = ECSEngine::SpriteComponent{score.digitTextureID[0], Rect{{0.0f, 0.0f}, 40, 40}, false};
        em.AddComponent(score.digitID[i], location);
        em.AddComponent(score.digitID[i], sprite);
    }

    em.AddComponent(em.CreateEntity("score"), score);

    // Setup Camera
    Rect win = engine.GetWindowManager().GetWindowBounds();
    ECSEngine::CameraComponent cam{};
    cam.position = Point2D(kPlayerStart.x, win.height / 2.0f);
    cam.worldUnitsPerPixel = 1.0f;
    cam.hardExclusion = Rect{{0.1f * win.width, 0.0f}, 0.8f * win.width, win.height};
    cam.softExclusion = Rect{{0.3f * win.width, 0.0f}, 0.4f * win.width, win.height};
    cam.speed = 0.1f;
    EntityID camera = em.CreateEntity("camera");
    em.AddComponent(camera, cam);
    em.AddComponent(camera, ECSEngine::CameraFollower{player});

    // Add all systems
    auto& sm = engine.GetSystemManager();
    sm.AddSystem(std::make_unique<ECSEngine::CollisionLateSystem<COMPONENTS>>());
    sm.AddSystem(std::make_unique<ECSEngine::InputSystem<COMPONENTS>>());
    sm.AddSystem(std::make_unique<ECSEngine::GravitySystem<COMPONENTS>>());
    sm.AddSystem(std::make_unique<ECSEngine::MovementSystem<COMPONENTS>>());
    sm.AddSystem(std::make_unique<ECSEngine::CollisionSystem<COMPONENTS>>());
    sm.AddSystem(std::make_unique<ECSEngine::ScoreSystem<COMPONENTS>>());
    sm.AddSystem(std::make_unique<ECSEngine::CameraSystem<COMPONENTS>>());
    sm.AddSystem(std::make_unique<ECSEngine::SpriteSystem<COMPONENTS>>());
    sm.AddSystem(std::make_unique<ECSEngine::SpawnSystem<COMPONENTS>>());

    engine.Run();
    return 0;
}
