#include "MainWindow.h"
#include "entity/tanks/Tank.h"

MainWindow::MainWindow() {
    m_window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(Configuration::MainWindow::WIDTH, Configuration::MainWindow::HEIGHT),
            Configuration::MainWindow::TITLE.data());

    m_window->setFramerateLimit(Configuration::MainWindow::FPS_LIMIT);

    m_tank = std::make_unique<KV1>();

    m_window->setMouseCursorVisible(false);
}

void MainWindow::run() {
    while (m_window->isOpen()) {
        sf::Event event{};
        while (m_window->pollEvent(event) == true) {
            if (event.type == sf::Event::Closed) {
                m_window->close();
                break;
            }
        }

        m_window->clear();

        draw();

        m_window->display();
    }
}

void MainWindow::draw() {
    m_tank->drawOn(*m_window);
    m_cursor.drawOn(*m_window);
}
