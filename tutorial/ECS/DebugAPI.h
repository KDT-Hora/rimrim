#pragma once
#include "ECSConfig.h"
#include "ECSManager.h" // 相互参照注意: .cppでインクルード推奨だが構造上ここに記載

namespace ECS {
    // ECSManagerへの読み取りアクセスと、QueueManagerへの書き込みアクセスを提供
    class DebugAPI {
    public:
        DebugAPI(ECSManager& manager) : ecs(manager) {}

        // --- 読み取り (Read Only) ---
        // 実際のEntityが存在するか確認
        Signature GetSignature(EntityID entity) const;

        // コンポーネントの値を取得 (コピーではなくconst参照)
        template<typename T>
        const T* GetComponent(EntityID entity) const;

        // --- 書き込み (Deferred Command) ---
        // デバッグGUIからの値変更はキュー経由で行う
        template<typename T>
        void SetComponentValue(EntityID entity, T newValue);

    private:
        ECSManager& ecs;
    };
}