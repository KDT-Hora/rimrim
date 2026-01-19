#pragma once
#include "../ECSManager.h"
#include "../Component/Components.h" // 定義したコンポーネントをインクルード

class RenderSystem : public ECS::System {
public:

    ECS::Signature Init()override
    {
        ECS::Signature sig;
        sig.set(ECS::GetComponentTypeID<TransformComponent>(), true);
        sig.set(ECS::GetComponentTypeID<CircleShapeComponent>(), true);
        return sig;
    }

    void Update(ECS::ECSManager& ecs, float dt) override 
    {
        // ContextからWindowへの参照を取得
        auto& window = ecs.GetSysContext().window;

        for (auto const& entity : mEntities) {
            // コンポーネントの取得 (参照で受けて変更を反映させる)
            auto& transform = ecs.GetComponent<TransformComponent>(entity);
            auto& circle = ecs.GetComponent<CircleShapeComponent>(entity);

            // ECSのTransformデータをSFMLのShapeに適用
            circle.shape.setPosition(transform.position);
            circle.shape.setRotation(sf::degrees(transform.rotation));
            circle.shape.setScale(transform.scale);

            // 描画
            window.draw(circle.shape);
        }
    }
};