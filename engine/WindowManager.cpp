#include "WindowManager.h"

namespace ECSEngine {

WindowManager::WindowManager(unsigned int width, unsigned int height, const std::string& title)
    : mWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode({width, height}), title)) {
        mWorldCenter = Point2D(width / 2.0f, height / 2.0f);
        mWorldUnitsPerPixel = 1.0f;
    }

Point2D WindowManager::GetWindowCenter() const {
    auto size = mWindow->getSize();
    return Point2D(size.x / 2.0f, size.y / 2.0f);
}

std::shared_ptr<sf::RenderWindow> WindowManager::GetWindow() const { return mWindow; }

Rect WindowManager::GetWindowBounds() const {
    auto size = mWindow->getSize();
    return Rect{Point2D(0.0f, 0.0f), static_cast<float>(size.x), static_cast<float>(size.y)};
}

void WindowManager::DebugDrawRect(const Rect& r, int red, int green, int blue, int alpha) {
    Rect w = WorldToWindow(r);
    sf::RectangleShape rect(sf::Vector2f(w.width, w.height));
    rect.setPosition(sf::Vector2f(w.topLeft.x, w.topLeft.y));
    rect.setFillColor(sf::Color(red, green, blue, alpha));
    mWindow->draw(rect);
}

void WindowManager::DebugFrameRect(const Rect& r, int red, int green, int blue, int alpha) {
    Rect w = WorldToWindow(r);
    sf::RectangleShape rect(sf::Vector2f(w.width, w.height));
    rect.setPosition(sf::Vector2f(w.topLeft.x, w.topLeft.y));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(red, green, blue, alpha));
    rect.setOutlineThickness(1.0f);
    mWindow->draw(rect);
}

Rect WindowManager::WindowToWorld(const Rect& rect) const {
    return Rect{
        WindowToWorld(rect.topLeft),
        WindowToWorld(rect.width),
        WindowToWorld(rect.height)
    };
}

Point2D WindowManager::WindowToWorld(const Point2D& pt) const {
    Point2D windowCenter = GetWindowCenter();
    return Point2D
                (mWorldCenter.x + (pt.x - windowCenter.x) * mWorldUnitsPerPixel,
                mWorldCenter.y + (pt.y - windowCenter.y) * mWorldUnitsPerPixel);
}

Rect WindowManager::WorldToWindow(const Rect& rect) const {
    return Rect{
        WorldToWindow(rect.topLeft),
        WorldToWindow(rect.width),
        WorldToWindow(rect.height)
    };
}

Point2D WindowManager::WorldToWindow(const Point2D& pt) const {
    Point2D windowCenter = GetWindowCenter();
    return Point2D
                (windowCenter.x + (pt.x - mWorldCenter.x) / mWorldUnitsPerPixel,
                windowCenter.y + (pt.y - mWorldCenter.y) / mWorldUnitsPerPixel);
}

void WindowManager::SetCamera(const Point2D& worldPt, const Point2D& screenPt) {
    Point2D windowCenter = GetWindowCenter();
    mWorldCenter = Point2D
                    (worldPt.x - (screenPt.x - windowCenter.x) * mWorldUnitsPerPixel,
                    worldPt.y - (screenPt.y - windowCenter.y) * mWorldUnitsPerPixel);
}

Point2D WindowManager::GetWorldCenter() const { return mWorldCenter; }

float WindowManager::GetWorldScale() const { return mWorldUnitsPerPixel; }

void WindowManager::SetWorldCenter(const Point2D& worldCenter) { mWorldCenter = worldCenter; }

void WindowManager::SetWorldScale(float worldUnitsPerPixel) { mWorldUnitsPerPixel = worldUnitsPerPixel; }

void WindowManager::SetWorldRect(const Rect& worldCameraRect) {
    Rect windowBounds = GetWindowBounds();
    mWorldCenter = Point2D
                    (worldCameraRect.topLeft.x + worldCameraRect.width / 2.0f,
                    worldCameraRect.topLeft.y + worldCameraRect.height / 2.0f);
    mWorldUnitsPerPixel = std::max(worldCameraRect.width / windowBounds.width, worldCameraRect.height / windowBounds.height);
}

float WindowManager::WindowToWorld(float x) const {
    return x * mWorldUnitsPerPixel;
}

float WindowManager::WorldToWindow(float x) const {
    return x / mWorldUnitsPerPixel;
}

}  // namespace ECSEngine
