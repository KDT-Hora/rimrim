#pragma once
#include "ECSConfig.h"
#include <array>

namespace ECS {
    class EntityManager {
    public:
        EntityManager() {
            livingEntityCount = 0;
            for (EntityID i = 0; i < MAX_ENTITIES; ++i) {
                availableEntities.push(CreateEntityID(i, 0)); // 初期世代は0
                signatures[i].reset();
            }
        }

        EntityID CreateEntity() {
            assert(livingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

            EntityID id = availableEntities.front();
            availableEntities.pop();
            livingEntityCount++;

            return id;
        }

        void DestroyEntity(EntityID entity) {
            assert(livingEntityCount > 0 && "No entities to destroy.");

            // シグネチャをリセット
            EntityID index = GetEntityIndex(entity);
            signatures[index].reset();

            // 世代を更新してプールに戻す
            uint16_t gen = GetEntityGeneration(entity);
            availableEntities.push(CreateEntityID(index, gen + 1));

            livingEntityCount--;
        }

        void SetSignature(EntityID entity, Signature signature) {
            signatures[GetEntityIndex(entity)] = signature;
        }

        Signature GetSignature(EntityID entity) const {
            return signatures[GetEntityIndex(entity)];
        }

        // アクティブなエンティティ一覧を返す（デバッグ用など）
        // ※効率化のため本来はリスト管理推奨だが、ここでは簡易スキャン
        std::vector<EntityID> GetActiveEntities() const {
            std::vector<EntityID> actives;
            // 実装詳細: ここは要件に応じて最適化可能
            // 現状はプールにあるものを除外する等のロジックが必要だが、
            // 簡易的に全スキャンするか、別途アクティブリストを持つのが一般的。
            // 今回は割愛。
            return actives;
        }

    private:
        std::queue<EntityID> availableEntities;
        std::array<Signature, MAX_ENTITIES> signatures;
        uint32_t livingEntityCount;
    };
}