#pragma once

#include "SFML/Window.hpp"

namespace Configuration {
    namespace MainWindow {
        constexpr static uint16_t WIDTH = 1920;
        constexpr static uint16_t HEIGHT = 1080;

        constexpr static std::string_view TITLE = "8bitTanksGame";
        constexpr static uint16_t FPS_LIMIT = 60;
    };

    namespace Controls {
        constexpr static sf::Mouse::Button ALTERNATIVE_WEAPON = sf::Mouse::Button::Right;
        constexpr static sf::Mouse::Button MAIN_WEAPON = sf::Mouse::Button::Left;

        constexpr static sf::Keyboard::Key FORWARD = sf::Keyboard::Key::W;
        constexpr static sf::Keyboard::Key LEFT = sf::Keyboard::Key::A;
        constexpr static sf::Keyboard::Key BACK = sf::Keyboard::Key::S;
        constexpr static sf::Keyboard::Key RIGHT = sf::Keyboard::Key::D;
    };

    namespace Textures {
        constexpr static std::string_view CURSOR = "resources/cursor/attack.png";
        constexpr static std::string_view HULL = "resources/textures/KV-1/hull.png";
        constexpr static std::string_view TURRET = "resources/textures/KV-1/turret.png";
    }
};