#include "ECSManager.h"
#include <cmath>

namespace ECS 
{

    EntityID ECSManager::CreateEntity() {
        return entityManager->CreateEntity();
    }

    void ECSManager::DestroyEntity(EntityID entity) {
        entityManager->DestroyEntity(entity);
        componentManager->EntityDestroyed(entity);
        systemManager->EntityDestroyed(entity);
    }

    //  ECS更新
    //  全システムの更新
    //  システムによって更新タイミングを分ける必要アリ？
    void ECSManager::Update(float deltaTime) 
    {

        // 2. ゲーム速度倍率に応じたループ回数の決定
        // 例: 倍率 1.0 -> 1回, 倍率 2.5 -> 2回 (端数切捨て) または ceilで3回
        float multiplier = sysContext.gameSpeedMultiplier;

        // 簡易的な実装: 整数回ループ
        int iterations = static_cast<int>(std::floor(multiplier));

        // 必要なら端数時間を別途蓄積して確率的に回数を増やす処理も可能
        // float remainder = multiplier - iterations;

        // 固定デルタタイムを使用
        float dt = sysContext.fixedDeltaTime;

        // 3. システム更新ループ
        for (int i = 0; i < iterations; ++i) {
            for (auto const& pair : systemManager->systems) {
                auto const& system = pair.second;
                system->Update(*this, dt);
            }
        }

        // 4. フレーム末尾処理: Queueの実行 (Entity生成/破棄、コンポーネント変更)
        queueManager->Execute();
    }


}