#pragma once
#include "../ECSManager.h"
#include "../Component/Components.h" 

class PlayerMoveSystem : public ECS::System {
public:

    ECS::Signature Init()override
    {
        ECS::Signature sig;
        sig.set(ECS::GetComponentTypeID<TransformComponent>(), true);
        sig.set(ECS::GetComponentTypeID<MoveValueComponent>(), true);
        return sig;
    }

    void Update(ECS::ECSManager& ecs, float dt) override 
    {
        // ContextからWindowへの参照を取得
        auto& window = ecs.GetSysContext().window;

        for (auto const& entity : mEntities)
        {
            // コンポーネントの取得 (参照で受けて変更を反映させる)
            auto& transform = ecs.GetComponent<TransformComponent>(entity);
            auto& moveValue = ecs.GetComponent<MoveValueComponent>(entity);

            transform.position += moveValue.moveValue;
        }
    }
};