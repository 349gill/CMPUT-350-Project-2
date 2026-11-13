#pragma once

#include <vector>

#include "CameraComponent.h"
#include "CollisionComponent.h"
#include "EntityManager.h"
#include "InputComponent.h"
#include "LocationComponent.h"
#include "MathUtil.h"
#include "ScoreComponent.h"
#include "SoundManager.h"
#include "SpawnComponent.h"
#include "SpriteComponent.h"
#include "SpriteManager.h"
#include "SystemManager.h"
#include "WindowManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace ECSEngine {

template <typename... Components>
class EngineView {
public:
    virtual SoundManager& GetSoundManager() = 0;
    virtual SpriteManager& GetSpriteManager() = 0;
    virtual EntityManager<Components...>& GetEntityManager() = 0;
    virtual WindowManager& GetWindowManager() = 0;
};

template <typename... Components>
class ECSEngine : public EngineView<Components...> {
public:
    ECSEngine(unsigned int width, unsigned int height, const std::string& name);
    ~ECSEngine();

    void Run();

    SoundManager& GetSoundManager() override { return mSoundManager; }

    SpriteManager& GetSpriteManager() override { return mSpriteManager; }

    EntityManager<Components...>& GetEntityManager() override { return mEntityManager; }

    WindowManager& GetWindowManager() override { return mWindowManager; }

    SystemManager<Components...>& GetSystemManager() { return mSystemManager; }

private:
    bool ProcessEvents();
    void DebugDraw();

    EntityManager<Components...> mEntityManager;
    SystemManager<Components...> mSystemManager;
    SpriteManager mSpriteManager;
    SoundManager mSoundManager;
    WindowManager mWindowManager;

    // For debugging - pause and step the engine
    bool running, step;
    int debug;
};

template <typename... Components>
ECSEngine<Components...>::ECSEngine(unsigned int width, unsigned int height, const std::string& name)
    : mWindowManager(width, height, name), running(true), step(false), debug(0) 
    { mWindowManager.GetWindow()->setFramerateLimit(60); }

template <typename... Components>
ECSEngine<Components...>::~ECSEngine() {}

template <typename... Components>
void ECSEngine<Components...>::Run() {
    auto window = mWindowManager.GetWindow();
    while (window->isOpen()) {
        if (!ProcessEvents()) {
            break; // Process events
        };

        if (!running && !step) continue;

        step = false;
        window->clear(); // Clear window

        if (!mSystemManager.Run(this)) {
            break; // Run systems
        }

        if (debug) {
            DebugDraw();
        }
        window->display(); // Render frame
    }
    window->close();
}

// F1: Toggle debug drawing
// F2: Pause
// F3: Walk-through step
template <typename... Components>
bool ECSEngine<Components...>::ProcessEvents() {
    auto window = mWindowManager.GetWindow();
    while (const std::optional event = window->pollEvent()) {
        if (event->template is<sf::Event::Closed>()) return false;

        const auto* pressed = event->template getIf<sf::Event::KeyPressed>();
        const auto* released = event->template getIf<sf::Event::KeyReleased>();
        if (!pressed && !released) continue;

        sf::Keyboard::Scancode code = pressed ? pressed->scancode : released->scancode;
        if (code == sf::Keyboard::Scancode::Unknown) continue;
        bool down = (pressed != nullptr);

        if (down && code == sf::Keyboard::Scancode::F1) 
        {
            debug = !debug;
        }
        if (down && code == sf::Keyboard::Scancode::F2) 
        {
            running = !running;
        }
        if (down && code == sf::Keyboard::Scancode::F3) 
        {
            step = true;
        }

        // Process Input
        for (const auto& entity : mEntityManager) {
            EntityID id = entity.GetID();
            if (!mEntityManager.IsValid(id)) continue;
            if (!mEntityManager.template HasComponent<InputComponent>(id)) continue;
            auto& input = mEntityManager.template GetComponent<InputComponent>(id);
            input.keydown[static_cast<size_t>(code)] = down;
        }
    }
    return true;
}

template <typename... Components>
void ECSEngine<Components...>::DebugDraw() {
    for (const auto& entity : mEntityManager) {
        EntityID id = entity.GetID();
        if (!mEntityManager.IsValid(id))
            continue;
        if (!mEntityManager.template HasComponent<LocationComponent>(id))
            continue;
        if (!mEntityManager.template HasComponent<CollisionComponent>(id))
            continue;
        
        const Point2D& loc = mEntityManager.template GetComponent<LocationComponent>(id).loc;
        const Rect& box = mEntityManager.template GetComponent<CollisionComponent>(id).collisionBox;
        Rect world{Point2D(loc.x + box.topLeft.x, loc.y + box.topLeft.y), box.width, box.height};
        mWindowManager.DebugFrameRect(world, 255, 0, 0);
    }
}

}  // namespace ECSEngine
