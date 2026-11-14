#include "SpriteManager.h"

namespace ECSEngine {

SpriteID SpriteManager::RegisterTexture(const std::string& texturePath, const Rect& sourceRect) {
    auto texture = mTextures.find(texturePath);
    if (texture == mTextures.end()) {
        sf::Texture newTexture;
        if (!newTexture.loadFromFile(texturePath)) {
            // TODO: Throw an exception
            return 0;
        }
        texture = mTextures.emplace(texturePath, std::move(newTexture)).first;
    }
    sf::IntRect rect(
    {static_cast<int>(sourceRect.topLeft.x), static_cast<int>(sourceRect.topLeft.y)},
    {static_cast<int>(sourceRect.width), static_cast<int>(sourceRect.height)});
    if (sourceRect.width <= 0 || sourceRect.height <= 0) {
        rect = sf::IntRect({0, 0}, sf::Vector2i(texture->second.getSize()));
    }
    mSprites.emplace_back(texture->second, rect);
    return mSprites.size() - 1;
}

sf::Sprite& SpriteManager::GetSprite(SpriteID id) {
    return mSprites.at(id);
}

}  // namespace ECSEngine
