#include "MainWindow.h"

MainWindow::MainWindow() {
    m_window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(Configuration::MainWindow::WIDTH, Configuration::MainWindow::HEIGHT),
            Configuration::MainWindow::TITLE.data());

    m_window->setFramerateLimit(Configuration::MainWindow::FPS_LIMIT);

    m_tank = std::make_unique<Hull>();
    m_turret = std::make_unique<Turret>(*m_tank, *m_window);

    m_window->setMouseCursorVisible(false);
}

void MainWindow::run() {
    while (m_window->isOpen()) {
        sf::Event event{};
        while (m_window->pollEvent(event) == true) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
            }
        }

        auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(*m_window));

        m_turret->updateRotation();

        m_cursor.setPosition(mousePosition);

        m_tank->handlePlayerInputs();

        handleProjectiles();

        m_window->clear();

        draw();

        m_window->display();
    }
}

void MainWindow::draw() {
    m_window->draw(m_tank->getSprite());
    m_turret->draw(*m_window);

    m_window->draw(m_cursor.getSprite());

    for (const auto& projectile : m_projectiles) {
        m_window->draw(projectile->getShapeObject());
    }
}

void MainWindow::handleProjectiles() {
    constexpr float mainWeaponReloadTime = 1.0f;
    if (sf::Mouse::isButtonPressed(Configuration::Controls::MAIN_WEAPON)) {
        if (m_shellClock.getElapsedTime().asSeconds() > mainWeaponReloadTime) {
            m_projectiles.push_front(std::make_unique<Shell>(*m_turret));
            m_shellClock.restart();
        }
    }

    constexpr float altWeaponReloadTime = 0.15f;
    if (sf::Mouse::isButtonPressed(Configuration::Controls::ALTERNATIVE_WEAPON)) {
        if (m_bulletClock.getElapsedTime().asSeconds() > altWeaponReloadTime) {
            m_projectiles.push_front(std::make_unique<Bullet>(*m_turret));
            m_bulletClock.restart();
        }
    }

    while (!m_projectiles.empty() && !m_projectiles.front()->isWithinScreenBounds()) {
        m_projectiles.front().reset();
        m_projectiles.pop_front();
    }

    for (const auto& projectile : m_projectiles) {
        projectile->updatePosition();
    }
}
