#pragma once
#include "../ECSManager.h"
#include "../Component/Components.h" // 定義したコンポーネントをインクルード
#include "../../Game/Constants.h"

class EntityRenderSystem : public ECS::System {
public:

    ECS::Signature Init()override
    {
        ECS::Signature sig;
        sig.set(ECS::GetComponentTypeID<GridPositionComponent>(), true);
        sig.set(ECS::GetComponentTypeID<DebugRendererComponent>(), true);
        return sig;
    }

    void Update(ECS::ECSManager& ecs, float dt) override
    {
        // ContextからWindowへの参照を取得
        auto& window = ecs.GetSysContext().window;

        for (auto const& entity : mEntities) {
            // コンポーネントの取得 (参照で受けて変更を反映させる)
            auto& gridPos = ecs.GetComponent<GridPositionComponent>(entity);
            auto& dbgRender = ecs.GetComponent<DebugRendererComponent>(entity);

            float size = TILE_SIZE * 0.8f;
            float offset = (TILE_SIZE - size) / 2.0f;

            sf::RectangleShape shape(sf::Vector2f(size, size));
            shape.setFillColor(dbgRender.color);

            // グリッド座標 -> 画面ピクセル座標 への変換
            float pixelX = gridPos.x * TILE_SIZE + offset;
            float pixelY = gridPos.y * TILE_SIZE + offset;

            shape.setPosition({ pixelX, pixelY });

            // 描画
            window.draw(shape);
        }
    }
};