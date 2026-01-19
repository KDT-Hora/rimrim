#pragma once
#include "ECSConfig.h"
#include "../Context/SystemContext.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "QueueManager.h"
#include "EventBus.h"
#include <memory>

namespace ECS {

    class ECSManager {
    public:
        ECSManager(engine::SystemContext& ctx) 
            : sysContext(ctx) 
        {
            componentManager = std::make_unique<ComponentManager>();
            entityManager = std::make_unique<EntityManager>();
            systemManager = std::make_unique<SystemManager>();
            queueManager = std::make_unique<QueueManager>();
            eventBus = std::make_unique<EventBus>();
        }


        // --- メインループ ---

        //  システム更新
        void Update(float deltaTime);
        //  

        // --- Entity管理 (QueueManager経由推奨だが、初期化時は直接呼ぶことも) ---
        EntityID CreateEntity();
        void DestroyEntity(EntityID entity);

        // --- コンポーネント管理 ---
        template<typename T>
        void RegisterComponent() {
            componentManager->RegisterComponent<T>();
        }

        //  コンポーネント追加
        template<typename T>
        void AddComponent(EntityID entity, T component) {
            componentManager->AddComponent<T>(entity, component);

            auto signature = entityManager->GetSignature(entity);
            signature.set(GetComponentTypeID<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        //  コンポーネント除外
        template<typename T>
        void RemoveComponent(EntityID entity) {
            componentManager->RemoveComponent<T>(entity);

            auto signature = entityManager->GetSignature(entity);
            signature.set(GetComponentTypeID<T>(), false);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChanged(entity, signature);
        }

        //  コンポーネント取得
        template<typename T>
        T& GetComponent(EntityID entity) {
            return componentManager->GetComponent<T>(entity);
        }

        template<typename T>
        const T& GetComponentConst(EntityID entity) const {
            return componentManager->GetComponentConst<T>(entity);
        }

        // --- システム管理 ---
        template<typename T>
        std::shared_ptr<T> RegisterSystem() {
            return systemManager->RegisterSystem<T>();
        }

        //  システムのシグネチャ登録
        template<typename T>
        void SetSystemSignature(Signature signature) {
            systemManager->SetSignature<T>(signature);
        }

        // --- アクセサ ---
        engine::SystemContext& GetSysContext() { return sysContext; }
        QueueManager& GetQueue() { return *queueManager; }
        EventBus& GetEventBus() { return *eventBus; }
        EntityManager& GetEntityManager() { return *entityManager; } // Debug用

    private:
        engine::SystemContext& sysContext;
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<SystemManager> systemManager;
        std::unique_ptr<QueueManager> queueManager;
        std::unique_ptr<EventBus> eventBus;
    };
}

// DebugAPIの実装の一部をヘッダー展開のためにここに記載
#include "DebugAPI.h"
namespace ECS 
{

    inline Signature DebugAPI::GetSignature(EntityID entity) const {
        return ecs.GetEntityManager().GetSignature(entity);
    }

    template<typename T>
    const T* DebugAPI::GetComponent(EntityID entity) const {
        // 安全に取得できるかチェックするロジックが必要
        return &ecs.GetComponentConst<T>(entity);
    }

    template<typename T>
    void DebugAPI::SetComponentValue(EntityID entity, T newValue) {
        ecs.GetQueue().AddCommand([this, entity, newValue]() {
            // フレーム末尾で実行
            if (ecs.GetEntityManager().GetSignature(entity).test(GetComponentTypeID<T>())) {
                ecs.GetComponent<T>(entity) = newValue;
            }
            });
    }
}