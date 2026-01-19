#pragma once
#include <vector>
#include <functional>

namespace ECS {
    class QueueManager {
    public:
        using Command = std::function<void()>;

        // コマンドをキューに追加（例: Entity作成、コンポーネント追加など）
        void AddCommand(Command command) {
            commandQueue.push_back(command);
        }

        // フレーム末尾で一括実行
        void Execute() {
            for (const auto& command : commandQueue) {
                command();
            }
            commandQueue.clear();
        }

    private:
        std::vector<Command> commandQueue;
    };
}