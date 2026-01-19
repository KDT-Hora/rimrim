#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

#include "Context/SystemContext.h"
#include "Game/GameSession.h"
#include "System/Scene/SceneManager.h"
#include "System/Scene/Title/TitleScene.h" //<- 最初のシーンとして仮に指定

/*
 * 【構造改革案】
 *
 * 1. main関数が全ての主要オブジェクトを所有する
 *    - sf::RenderWindow, SystemContext, GameSession, SceneManager
 *    - これにより、所有権が明確になり、シングルトンへの依存がなくなります。
 *
 * 2. ゲームループをシンプルにする
 *    - イベント処理 -> 更新 -> 描画 の明確な分離。
 *    - 全ての更新と描画はSceneManagerに委譲します。
 *
 * 3. グローバルなインスタンスの廃止
 *    - SceneManager::Instance() を使わず、mainで生成したオブジェクトを渡していきます。
 */

int main() {
    // 1. 主要オブジェクトの初期化
    // SFML 3.xではポインタで管理する必要はありません
    unsigned int width = 1280;
    unsigned int height = 720;
    sf::RenderWindow window(sf::VideoMode({width, height}), "RimClone");
    window.setFramerateLimit(60);

    // ImGuiの初期化
    ImGui::SFML::Init(window);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // ゲームのコアコンポーネントをmain関数で所有
    engine::SystemContext context(window);
    game::GameSession gameSession;
    SceneManager sceneManager; // <- シングルトンではなく、通常オブジェクトとして生成

    // 2. 依存関係の注入（DI）
    // GameSessionとSceneManagerに必要な初期設定を行う
    gameSession.Init(context);
    sceneManager.SetGameSession(&gameSession); // SceneManagerにGameSessionを渡す

    // 最初のシーンをリクエスト
    sceneManager.RequestChange<TitleScene>();


    sf::Clock clock;
    while (window.isOpen()) {
        // 3. ゲームループ
        sf::Time dt = clock.restart();

        // --- イベント処理 (SFML 3.x 形式) ---
        while (const std::optional<sf::Event> eventOptional = window.pollEvent()) {
            const sf::Event& event = *eventOptional;
            ImGui::SFML::ProcessEvent(window, event);
            if (event.is<sf::Event::Closed>())
            {
                std::cout << "Window close" << std::endl;
                window.close();
            }
            // シーンにイベントを渡す
            sceneManager.HandleEvent(event);
        }

        // --- 更新 ---
        ImGui::SFML::Update(window, dt);
        sceneManager.Update(dt); // SceneManager経由で現在のシーンを更新

        // --- 描画 ---
        window.clear(sf::Color(30,30,30)); // 背景色

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); // ImGui DockSpace

        sceneManager.Render(window); // SceneManager経由で現在のシーンを描画
        
        ImGui::SFML::Render(window); // ImGuiのUIを描画

        window.display();
    }
    //while (window->isOpen()) {
    //    sf::Time dt = clock.restart();
    //    while (const std::optional<sf::Event> eventOptional = window->pollEvent()) {
    //        const sf::Event& event = *eventOptional;
    //        ImGui::SFML::ProcessEvent(*window, event);
    //        if (event.is<sf::Event::Closed>())
    //        {
    //            std::cout << "Window close" << std::endl;
    //            window->close();
    //        }
    //    }
    //    window->clear();
    //    ImGui::SFML::Update(*window, clock.restart());
    //    //	ウィンドウの端とかにつけるやつ
    //    //	画面が見たい時はこれをオフにする
    //    //	切り替えで管理する
    ////	ImGuiViewport* id = ImGui::GetMainViewport();
    ////	ImGui::DockSpaceOverViewport(id->ID);

    //    ImGui::Begin("ECS Inspector");
    //    ImGui::End();

    //    gameSession.Update();
    //    ImGui::SFML::Render(*window);
    //    window->display();
    //}

    // 終了処理
    ImGui::SFML::Shutdown();

    return 0;
}
