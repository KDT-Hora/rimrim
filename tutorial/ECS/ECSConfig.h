#pragma once
#include <cstdint>
#include <bitset>
#include <vector>
#include <queue>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <cassert>

namespace ECS 
{

    // --- 定数と型定義 ---
    using EntityID = std::uint32_t;
    using ComponentTypeID = std::uint8_t;

    // エンティティ最大数とコンポーネント最大種類数
    constexpr EntityID MAX_ENTITIES = 10000;
    constexpr ComponentTypeID MAX_COMPONENTS = 64;

    using Signature = std::bitset<MAX_COMPONENTS>;

    // --- Entity ID ビット演算 (世代カウンタ実装) ---
    // 下位20ビット: インデックス, 上位12ビット: 世代
    constexpr int ENTITY_INDEX_BITS = 20;
    constexpr int ENTITY_GENERATION_BITS = 12;
    constexpr EntityID ENTITY_INDEX_MASK = (1 << ENTITY_INDEX_BITS) - 1;
    constexpr EntityID ENTITY_GENERATION_MASK = (1 << ENTITY_GENERATION_BITS) - 1;

    inline EntityID GetEntityIndex(EntityID id) { return id & ENTITY_INDEX_MASK; }
    inline uint16_t GetEntityGeneration(EntityID id) { return (id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }
    inline EntityID CreateEntityID(EntityID index, uint16_t generation) {
        return (index & ENTITY_INDEX_MASK) | ((generation & ENTITY_GENERATION_MASK) << ENTITY_INDEX_BITS);
    }


    // --- コンポーネントID生成ヘルパー ---
    inline ComponentTypeID GetUniqueComponentID() {
        static ComponentTypeID lastID = 0;
        return lastID++;
    }

    template <typename T>
    inline ComponentTypeID GetComponentTypeID() noexcept {
        static const ComponentTypeID typeID = GetUniqueComponentID();
        return typeID;
    }
}