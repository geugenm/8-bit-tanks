#pragma once

#include <SFML/Graphics.hpp>
#include "entity/Projectile.h"
#include "entity/Turret.h"
#include "MovementVectors.h"
#include "entity/Hull.h"
#include "Config.h"
#include "Cursor.h"
#include <SFML/Audio.hpp>
#include <list>


class MainWindow {
public:
    MainWindow();

    void run();

private:
    void draw();

    void handleProjectiles(const sf::Vector2f &mousePosition);


    std::unique_ptr<sf::RenderWindow> m_window;

    sf::Clock m_clock;

    sf::Clock m_shellClock;
    sf::Clock m_bulletClock;

    Hull m_tank;

    std::unique_ptr<Turret> m_turret;

    Cursor m_cursor;

    std::list<Projectile *> m_projectiles;
};
