#pragma once

#include <cassert>
#include <iostream>
#include <limits>
#include <type_traits>

#include "Component.h"
#include "Entity.h"

namespace ECSEngine {

template <typename T, typename... Ts>
struct Index;   // Index of type T in the parameter pack

template <typename T, typename... Ts>
struct Index<T, T, Ts...> : std::integral_constant<size_t, 0> {};

template <typename T, typename U, typename... Ts>
struct Index<T, U, Ts...> : std::integral_constant<size_t, 1 + Index<T, Ts...>::value> {};

template <typename... Components>
class EntityManager {
public:
    static constexpr size_t kNullComponent = std::numeric_limits<size_t>::max();

    [[nodiscard]] EntityID CreateEntity(const std::string& name) {
        EntityID index = mEntities.size();

        // TODO: Check whether to use emplace_back or push_back
        mEntities.push_back(Entity(index, name));
        mInvalid.push_back(false);
        
        std::array<size_t, sizeof...(Components)> componentIndices;
        componentIndices.fill(kNullComponent);
        mComponentIndices.push_back(componentIndices);

        return id;
    }

    bool IsValid(EntityID entity) const {
        return entity < mEntities.size() && !mInvalid[entity];
    }

    void RemoveEntity(EntityID entity) {
        if (!IsValid(entity)) {
            // TODO: Add logging
            return;
        }

        (RemoveComponent<Components>(entity), ...);
        mInvalid[entity] = true;
    }

    template <typename T>
    void AddComponent(EntityID entity, T component) {
        assert(IsValid(entity));

        auto& storage = std::get<ComponentStorage<T>>(mComponents);
        size_t& index = mComponentIndices[entity][Index<T, Components...>::value];

        if (index != kNullComponent) {
            storage.mStorage[index] = component; return;
        } 

        if (storage.mFreeList.empty()) {
            index = storage.mStorage.size();
            storage.mStorage.push_back(component);
            storage.mValid.push_back(true);
            return;
        }

        index = storage.mFreeList.back();
        storage.mFreeList.pop_back();
        storage.mStorage[index] = component;
        storage.mValid[index] = true; 
        return;
    }

    template <typename T>
    void RemoveComponent(EntityID entity) {
        if (!HasComponent<T>(entity)) {
            // TODO: Add logging
            return;
        }

        auto& storage = std::get<ComponentStorage<T>>(mComponents);
        size_t& index = mComponentIndices[entity][Index<T, Components...>::value];
        storage.mValid[index] = false;
        storage.mFreeList.push_back(index);
        index = kNullComponent;
    }

    template <typename T>
    bool HasComponent(EntityID entity) const {
        return IsValid(entity) && mComponentIndices[entity][Index<T, Components...>::value] != kNullComponent;
    }

    template <typename T>
    T& GetComponent(EntityID entity) {
        assert(HasComponent<T>(entity));
        return std::get<ComponentStorage<T>>(mComponents).mStorage[mComponentIndices[entity][Index<T, Components...>::value]];
    }

    template <typename T>
    ComponentStorage<T>& GetComponentStorage() {
        return std::get<ComponentStorage<T>>(mComponents);
    }

    using tEntity = std::vector<Entity>;
    using const_iterator = tEntity::const_iterator;

    const_iterator cbegin() const { return mEntities.begin(); }
    const_iterator cend() const { return mEntities.end(); }

    const_iterator begin() const { return mEntities.begin(); }
    const_iterator end() const { return mEntities.end(); }

private:
    std::vector<Entity> mEntities;  // Entity vector
    std::vector<bool> mInvalid; // Marking valid and invalid entries
    std::tuple<ComponentStorage<Components>...> mComponents; // Component storage
    std::vector<std::array<size_t, sizeof...(Components)>> mComponentIndices; // Component index table for each entity
};

}  // namespace ECSEngine
