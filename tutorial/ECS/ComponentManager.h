#pragma once
#include "ECSConfig.h"

namespace ECS {

    // コンポーネント配列の基底インターフェース
    class IComponentArray {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(EntityID entity) = 0;
    };

    // 型ごとのコンポーネント配列 (Packed Array)
    template<typename T>
    class ComponentArray : public IComponentArray {
    public:
        void InsertData(EntityID entity, T component) {
            size_t newIndex = componentArray.size();
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            componentArray.push_back(component);
        }

        void RemoveData(EntityID entity) {
            if (entityToIndexMap.find(entity) == entityToIndexMap.end()) return;

            // Swap & Pop 実装: 
            // 削除対象の要素を配列の最後の要素で上書きし、配列サイズを減らす
            size_t removedIndex = entityToIndexMap[entity];
            size_t lastIndex = componentArray.size() - 1;

            if (removedIndex != lastIndex) {
                T& lastComponent = componentArray[lastIndex];
                EntityID lastEntity = indexToEntityMap[lastIndex];

                componentArray[removedIndex] = lastComponent;
                indexToEntityMap[removedIndex] = lastEntity;
                entityToIndexMap[lastEntity] = removedIndex;
            }

            componentArray.pop_back();
            indexToEntityMap.erase(lastIndex);
            entityToIndexMap.erase(entity);
        }

        T& GetData(EntityID entity) {
            // 注意: 本来は境界チェック推奨
            return componentArray[entityToIndexMap[entity]];
        }

        // Debug API用 (const参照)
        const T& GetDataConst(EntityID entity) const {
            return componentArray.at(entityToIndexMap.at(entity));
        }

        void EntityDestroyed(EntityID entity) override {
            if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
                RemoveData(entity);
            }
        }

    private:
        // コンポーネントデータ (連続メモリ)
        std::vector<T> componentArray;

        // EntityID -> 配列インデックス のマップ
        std::unordered_map<EntityID, size_t> entityToIndexMap;

        // 配列インデックス -> EntityID のマップ (Swap処理用)
        std::unordered_map<size_t, EntityID> indexToEntityMap;
    };

    class ComponentManager {
    public:
        template<typename T>
        void RegisterComponent() {
            ComponentTypeID typeID = GetComponentTypeID<T>();
            componentArrays[typeID] = std::make_shared<ComponentArray<T>>();
        }

        template<typename T>
        void AddComponent(EntityID entity, T component) {
            GetComponentArray<T>()->InsertData(entity, component);
        }

        template<typename T>
        void RemoveComponent(EntityID entity) {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template<typename T>
        T& GetComponent(EntityID entity) {
            return GetComponentArray<T>()->GetData(entity);
        }

        template<typename T>
        const T& GetComponentConst(EntityID entity) const {
            return GetComponentArrayConst<T>()->GetDataConst(entity);
        }



        void EntityDestroyed(EntityID entity) {
            for (auto const& pair : componentArrays) {
                auto const& component = pair.second;
                component->EntityDestroyed(entity);
            }
        }

    private:
        std::unordered_map<ComponentTypeID, std::shared_ptr<IComponentArray>> componentArrays;

        template<typename T>
        std::shared_ptr<ComponentArray<T>> GetComponentArray() {
            return std::static_pointer_cast<ComponentArray<T>>(componentArrays[GetComponentTypeID<T>()]);
        }

        template<typename T>
        std::shared_ptr<const ComponentArray<T>> GetComponentArrayConst() const {
            return std::static_pointer_cast<const ComponentArray<T>>(componentArrays.at(GetComponentTypeID<T>()));
        }
    };
}