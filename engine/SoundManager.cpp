#include "SoundManager.h"

namespace ECSEngine {

void SoundManager::RegisterSound(const std::string& soundPath, const std::string& soundName) {
    auto sound = mSoundBuffers.find(soundPath);
    if (sound == mSoundBuffers.end()) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(soundPath)) {
            // TODO: Throw an exception
            return;
        }
        sound = mSoundBuffers.emplace(soundPath, std::move(buffer)).first;
    }

    mSounds[soundName] = mSoundInstances.size();
    mSoundInstances.emplace_back(sound->second); return;
}

sf::Sound& SoundManager::GetSound(const std::string& soundName) {
    return mSoundInstances.at(mSounds.at(soundName));
}

}  // namespace ECSEngine
