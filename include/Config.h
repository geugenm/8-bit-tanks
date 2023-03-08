#pragma once

#include "SFML/Window.hpp"

namespace Configuration {
    struct MainWindow {
        constexpr static uint32_t WIDTH = 1920;
        constexpr static uint32_t HEIGHT = 1080;

        constexpr static char* TITLE = "8bitTanksGame";
        constexpr static uint16_t FPS_LIMIT = 60;
    };

    struct Controls {
        constexpr static sf::Mouse::Button ALTERNATIVE_WEAPON = sf::Mouse::Button::Right;
        constexpr static sf::Mouse::Button MAIN_WEAPON = sf::Mouse::Button::Left;

        constexpr static sf::Keyboard::Key FORWARD = sf::Keyboard::Key::W;
        constexpr static sf::Keyboard::Key LEFT = sf::Keyboard::Key::A;
        constexpr static sf::Keyboard::Key BACK = sf::Keyboard::Key::S;
        constexpr static sf::Keyboard::Key RIGHT = sf::Keyboard::Key::D;

        constexpr static sf::Keyboard::Key INTERACT = sf::Keyboard::Key::E;
        constexpr static sf::Keyboard::Key RELOAD = sf::Keyboard::Key::R;
    };


};