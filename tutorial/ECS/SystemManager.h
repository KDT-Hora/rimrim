#pragma once
#include "ECSConfig.h"
#include <set>

namespace ECS {

    class ECSManager; // 前方宣言

    class System {
    public:
        std::set<EntityID> mEntities; // このシステムが処理する対象Entity
        virtual ~System() = default;
        virtual Signature Init() = 0;   //  必要シグネチャを返す初期化メソッド
        virtual void Update(ECSManager& ecs, float dt) = 0;
    };

    class SystemManager {
    public:
        template<typename T>
        std::shared_ptr<T> RegisterSystem() {
            ComponentTypeID typeID = std::type_index(typeid(T)).hash_code(); // 簡易ID
            auto system = std::make_shared<T>();
            systems.insert({ typeID, system });
            return system;
        }

        template<typename T>
        void SetSignature(Signature signature) {
            ComponentTypeID typeID = std::type_index(typeid(T)).hash_code();
            signatures.insert({ typeID, signature });
        }

        void EntityDestroyed(EntityID entity) {
            for (auto const& pair : systems) {
                auto const& system = pair.second;
                system->mEntities.erase(entity);
            }
        }

        // Entityのコンポーネント構成が変わったときにシステムへの登録状況を更新
        void EntitySignatureChanged(EntityID entity, Signature entitySignature) {
            for (auto const& pair : systems) {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemSignature = signatures[type];

                // システムが必要とする要件(ビット)を満たしているか
                if ((entitySignature & systemSignature) == systemSignature) {
                    system->mEntities.insert(entity);
                }
                else {
                    system->mEntities.erase(entity);
                }
            }
        }

        std::unordered_map<size_t, std::shared_ptr<System>> systems;
        std::unordered_map<size_t, Signature> signatures;
    };
}