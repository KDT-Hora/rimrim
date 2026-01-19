#include "Input.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

void InputManager::update(const sf::Event& event) {

    //  古い書き方の場合はこのような書き方
 //   if (event.type() == sf::Event::KeyPressed) {
 //       // キーが押されたイベント
 //       sf::Keyboard::Key key = event.key.code;
 //       if (keyStates[key] != KeyState::Held) {
 //           // Held状態でない場合のみ、Pressedに設定
 //           keyStates[key] = KeyState::Pressed;
 //       }
 //   }
 //   else if (event.type == sf::Event::KeyReleased) {
 //       // キーが離されたイベント
 //       sf::Keyboard::Key key = event.key.code;
 //       keyStates[key] = KeyState::Released;
 //   }

    // KeyPressed イベントのチェックとデータの取得
    // getIf<T>() は、イベントが一致すればそのイベントデータへのポインタを返し、
    // 一致しなければ nullptr を返します。
    if (const auto* keyPressedEvent = event.getIf<sf::Event::KeyPressed>()) {
        // キーが押されたイベント
        sf::Keyboard::Key key = keyPressedEvent->code; // データはポインタ経由で取得
        if (keyStates[key] != KeyState::Held) {
            keyStates[key] = KeyState::Pressed;
        }
    }
    // KeyReleased イベントのチェックとデータの取得
    else if (const auto* keyReleasedEvent = event.getIf<sf::Event::KeyReleased>()) {
        // キーが離されたイベント
        sf::Keyboard::Key key = keyReleasedEvent->code; // データはポインタ経由で取得
        keyStates[key] = KeyState::Released;
    }
}

void InputManager::reset() {
    for (auto& pair : keyStates) {
        if (pair.second == KeyState::Pressed) {
            // Pressed (今押された) は Held (押され続けている) に移行
            pair.second = KeyState::Held;
        }
        else if (pair.second == KeyState::Released) {
            // Released (今離された) は None (無効) に移行
            pair.second = KeyState::None;
        }
    }
}

bool InputManager::isKeyPressed(sf::Keyboard::Key key) const {
    auto it = keyStates.find(key);
    return (it != keyStates.end() && it->second == KeyState::Pressed);
}

bool InputManager::isKeyHeld(sf::Keyboard::Key key) const {
    auto it = keyStates.find(key);
    return (it != keyStates.end() && (it->second == KeyState::Held || it->second == KeyState::Pressed));
}

bool InputManager::isKeyRelease(sf::Keyboard::Key key) const
{
    auto it = keyStates.find(key);
    return (it != keyStates.end() && (it->second == KeyState::Released));
}
