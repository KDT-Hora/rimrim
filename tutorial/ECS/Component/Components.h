#pragma once
#include <SFML/Graphics.hpp>

// 位置、回転、拡大縮小を持つコンポーネント
struct TransformComponent 
{
    sf::Vector2f position = { 0.f, 0.f };
    float rotation = 0.f;
    sf::Vector2f scale = { 1.f, 1.f };
};

// 見た目（形状）を持つコンポーネント
// SFMLのCircleShapeをラップします
struct CircleShapeComponent 
{
    sf::CircleShape shape;

    // コンストラクタで初期化しやすくする
    CircleShapeComponent(float radius = 20.f, sf::Color color = sf::Color::Cyan) {
        shape.setRadius(radius);
        shape.setFillColor(color);
        shape.setOrigin({ radius, radius }); // 中心を原点にする
    }
};

//  移動量のコンポーネント
struct MoveValueComponent
{
    sf::Vector2f moveValue = { 0.5f,0.2f };

};

//  マップ上の座標コンポーネント
struct GridPositionComponent
{
    int x;
    int y;

    sf::Vector2i ToVector() const { return sf::Vector2i(x, y); }

    //  オペレーターオーバーロード
    bool operator == (const GridPositionComponent& other)const {
        return x == other.x && y == other.y;
    }
    bool operator != (const GridPositionComponent& other)const {
        return !(*this == other);
    }

};

//  見た目を表すコンポーネント
struct DebugRendererComponent
{
    sf::Color color;
};