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


class Window {
public:
    Window() {
        m_window.setFramerateLimit(Configuration::MainWindow::FPS_LIMIT);
    }

    void run() {
        m_window.setMouseCursorVisible(false);

        Turret turret(m_tank, m_window);

        while (m_window.isOpen()) {
            sf::Event event{};
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                }
            }

            if (m_window.hasFocus() == false) {
                continue;
            }

            auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(m_window));

            turret.update();

            m_cursor.setPosition(mousePosition);

            m_tank.handleInputs();

            const size_t projectileSizeBeforeShoot = m_projectiles.size();

            const float firePeriod = 1.0f;
            if (sf::Mouse::isButtonPressed(Configuration::Controls::MAIN_WEAPON)) {
                if (m_shellClock.getElapsedTime().asSeconds() > firePeriod) {
                    m_projectiles.push_front(new Shell(turret.getMuzzlePosition(), mousePosition));
                }
            }

            const float mainFirePeriod = 0.1f;
            if (sf::Mouse::isButtonPressed(Configuration::Controls::ALTERNATIVE_WEAPON)) {
                if (m_bulletClock.getElapsedTime().asSeconds() > mainFirePeriod) {
                    m_projectiles.push_front(new Bullet(turret.getPosition(), mousePosition));
                }
            }

            if (m_projectiles.size() != projectileSizeBeforeShoot) {
                m_shellClock.restart();
                m_bulletClock.restart();
                m_projectiles.front()->playSound();
            }

            for (const auto& projectile : m_projectiles) {
                projectile->update();
            }

            while (!m_projectiles.empty() && !m_projectiles.front()->isOnTheScreen()) {
                m_projectiles.pop_front();
            }

            m_window.clear();
            m_window.draw(m_tank.getSprite());
            turret.draw(m_window);

            m_window.draw(m_cursor.getSprite());

            for (const auto& projectile : m_projectiles) {
                m_window.draw(projectile->getShape());
            }

            m_window.display();

            m_clock.restart();
        }
    }

private:
    sf::RenderWindow m_window = sf::RenderWindow(
            sf::VideoMode(Configuration::MainWindow::WIDTH, Configuration::MainWindow::HEIGHT),
            Configuration::MainWindow::TITLE.data());

    sf::Clock m_clock;

    sf::Clock m_shellClock;
    sf::Clock m_bulletClock;

    Hull m_tank;

    Cursor m_cursor;

    std::list<Projectile *> m_projectiles;
};
