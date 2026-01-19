#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>

class InputManager {

    //  Singleton
    InputManager() = default;
public:
    InputManager(const InputManager&) = delete;
    void operator=(const InputManager&) = delete;
    static InputManager& Instance() {
        static InputManager instance;
        return instance;
    }

public:
    // キーの状態
    enum class KeyState {
        None,        // 状態なし
        Pressed,     // 今フレームで押された
        Held,        // 押され続けている
        Released     // 今フレームで離された
    };

private:
    // キーコードとキーの状態を格納するマップ
    std::unordered_map<sf::Keyboard::Key, KeyState> keyStates;

public:


    // SFMLイベントに基づいてキーの状態を更新
    void update(const sf::Event& event);

    // 全てのキーの状態をフレームの終わりにリセット
    void reset();

    // 特定のキーが今フレームで押されたか (一度だけ)
    bool isKeyPressed(sf::Keyboard::Key key) const;

    // 特定のキーが押され続けているか (Held or Pressed)
    bool isKeyHeld(sf::Keyboard::Key key) const;

    //  離した瞬間
    bool isKeyRelease(sf::Keyboard::Key key)const;

};