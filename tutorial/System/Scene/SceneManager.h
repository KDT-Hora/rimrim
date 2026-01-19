#pragma once
#include "../../temp/Singleton.h"
#include <memory>
#include "IScene.h"
#include <functional>
#include <type_traits>

namespace game
{
    class GameSession;
}

//	シーン管理クラス
class SceneManager :public Singleton<SceneManager>
{
    friend Singleton<SceneManager>;

private:

    game::GameSession* gameSession = nullptr;
    std::unique_ptr<IScene> currentScene;
    std::function<std::unique_ptr<IScene>()> nextSceneFactory = nullptr;

    SceneManager();
    ~SceneManager();

public:

    void SetGameSession(game::GameSession* session);

    void Init();

    template <typename T>
    void RequestChange()
    {
        if constexpr (std::is_base_of_v<IScene, T>)
        {
            nextSceneFactory = [this]() {
                return std::make_unique<T>(gameSession);
                };
        }
    }

    void Update();


};

/*
GameSessionの初期化
最初のシーンへの遷移
初期化処理
この順番で呼ぶこと
*/