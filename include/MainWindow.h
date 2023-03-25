#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <memory>

#include "entity/tanks/Tank.h"

#include "Config.h"
#include "Cursor.h"
#include "MovementVectors.h"


class MainWindow {
public:
    MainWindow();

    void run();

private:
    void draw();

    std::unique_ptr<sf::RenderWindow> m_window;

    std::unique_ptr<KV1> m_tank;

    Cursor m_cursor;
};
