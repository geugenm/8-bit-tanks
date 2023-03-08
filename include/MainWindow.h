#pragma once

#include <SFML/Graphics.hpp>
#include "entity/Projectile.h"
#include "entity/Turret.h"
#include "MovementVectors.h"
#include "entity/Tank.h"
#include "Config.h"
#include "Cursor.h"
#include <SFML/Audio.hpp>


class Window {
public:
    Window() {
        m_window.setFramerateLimit(Configuration::MainWindow::FPS_LIMIT);
    }

    void run() {
        m_window.setMouseCursorVisible(false);

        Tank tank;

        Cursor cursor;

        MachineGun bulletZero(tank.getTankCenterCoordinates(), tank.getTankCenterCoordinates());
        Shell shellZero(tank.getTankCenterCoordinates(), tank.getTankCenterCoordinates());
        std::vector<Shell> shells;
        std::vector<MachineGun> bullets;

        sf::Clock clock;
        sf::Clock soundBulletClock;

        while (m_window.isOpen()) {
            sf::Event event{};
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_window.close();
                }
            }

            Turret turret(tank.getTankCenterCoordinates());

            auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(m_window));

            turret.update(mousePosition);

            cursor.setPosition(mousePosition);

            tank.handleInputs();



            const float firePeriod = 1.0f;
            if (sf::Mouse::isButtonPressed(Configuration::Controls::MAIN_WEAPON)) {
                if (soundBulletClock.getElapsedTime().asSeconds() > firePeriod) {
                    shellZero.playSound();
                    Shell shell(Shell(turret.getPosition(), mousePosition));
                    shells.push_back(shell);
                    soundBulletClock.restart();
                }
            }

            const float mainFirePeriod = 0.1f;
            if (sf::Mouse::isButtonPressed(Configuration::Controls::ALTERNATIVE_WEAPON)) {
                if (soundBulletClock.getElapsedTime().asSeconds() > mainFirePeriod) {
                    bulletZero.playSound();
                    bullets.push_back(MachineGun(turret.getPosition(), mousePosition));
                    soundBulletClock.restart();
                }
            }

            for (auto bulletIter = shells.begin(); bulletIter != shells.end();) {
                bulletIter->update(clock.getElapsedTime().asSeconds());

                if (bulletIter->isOnTheScreen() == false) {
                    bulletIter = shells.erase(bulletIter);
                } else {
                    ++bulletIter;
                }
            }

            for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();) {
                bulletIter->update(clock.getElapsedTime().asSeconds());

                if (bulletIter->isOnTheScreen() == false) {
                    bulletIter = bullets.erase(bulletIter);
                } else {
                    ++bulletIter;
                }
            }

            DirectionVector tankDirectionVector(tank.getTankCenterCoordinates(), tank.getTankCenterCoordinates() +
                                                                                 tank.getDirectionVector().getDecartVector() *
                                                                                 100.0f, sf::Color::Red);
            DirectionVector targetDirectionVector(turret.getShape().getPosition(), sf::Vector2f(mousePosition),
                                                  sf::Color::Green);


            m_window.clear();
            m_window.draw(tank.getShape());
            m_window.draw(cursor.getShape());
            turret.draw(m_window);

            for (auto bullet: bullets) {
                m_window.draw(bullet.getShape());
            }

            for (auto shell: shells) {
                m_window.draw(shell.getShape());
            }

            //m_window.draw(tankDirectionVector.getShape());
            //m_window.draw(targetDirectionVector.getShape());

            m_window.display();

            clock.restart();
        }
    }

private:
    sf::RenderWindow m_window = sf::RenderWindow(
            sf::VideoMode(Configuration::MainWindow::WIDTH, Configuration::MainWindow::HEIGHT),
            Configuration::MainWindow::TITLE);

    sf::Clock m_clock;
};
