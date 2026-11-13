#pragma once

#include <unordered_map>

#include <SFML/Audio.hpp>

namespace ECSEngine {

class SoundManager {
public:
    SoundManager() = default;
    ~SoundManager() = default;
    void RegisterSound(const std::string& soundPath, const std::string& soundName);
    sf::Sound& GetSound(const std::string& soundName);

private:
    std::vector<sf::Sound> mSoundInstances;
    std::unordered_map<std::string, size_t> mSounds;
    std::unordered_map<std::string, sf::SoundBuffer> mSoundBuffers;
};

}  // namespace ECSEngine
