#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <memory>

#include "entity/Projectile.h"
#include "entity/Turret.h"
#include "entity/Hull.h"

#include "Config.h"
#include "Cursor.h"
#include "MovementVectors.h"


class MainWindow {
public:
    MainWindow();

    void run();

private:
    void draw();

    void handleProjectiles();


    std::unique_ptr<sf::RenderWindow> m_window;

    sf::Clock m_shellClock;
    sf::Clock m_bulletClock;

    std::unique_ptr<Hull> m_tank;

    std::unique_ptr<Turret> m_turret;

    Cursor m_cursor;

    std::deque<std::unique_ptr<Projectile>> m_projectiles;
};
