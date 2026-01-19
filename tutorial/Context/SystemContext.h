#pragma once
#include <SFML/Graphics.hpp>

namespace engine 
{

    struct SystemContext 
    {
        sf::RenderWindow& window;
        // ImGuiContext* imGuiContext; // 必要に応じて設定

        // 時間管理
        float gameSpeedMultiplier = 1.0f; // 1.0 = 等速, 2.0 = 2倍速
        float fixedDeltaTime = 1.0f / 60.0f; // 論理更新の固定時間ステップ


        SystemContext(sf::RenderWindow& win) : window(win) {}
    };
}