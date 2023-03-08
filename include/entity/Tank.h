#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Tank {
public:
    Tank() {
        m_shape.setPosition(375, 275);
        m_shape.setFillColor(sf::Color::White);
        m_shape.setSize(sf::Vector2f(80, 50));
        m_shape.setOrigin(m_shape.getSize() / 2.f);


        if (!m_texture.loadFromFile("resources/textures/tank.png")) {
            throw std::invalid_argument("Missing texture");
        }

        m_shape.setTexture(&m_texture);

        if (!m_tankMovementSound.openFromFile("resources/Wav/tank_move.wav")) {
            LOG(INFO) << "Tank movement sound is not found";
            throw std::invalid_argument("Tank movement sound is not found");
        }
        m_tankMovementSound.setLoop(true);

    }

    [[nodiscard]] sf::RectangleShape getShape() const {
        return m_shape;
    }

    const float soundPeriod = 0.01f;
    void PlayMovementSound() {
        if (m_moveSoundClock.getElapsedTime().asSeconds() > soundPeriod) {
            m_tankMovementSound.stop();
            return;
        }

        if (m_tankMovementSound.getStatus() == sf::SoundSource::Playing) {
            return;
        }

        m_tankMovementSound.play();

    }

    void handleInputs() {
        using namespace Configuration;
        float speed = 1.0f;
        sf::Vector2f changeVector = m_directionVector.getDecartVector() * speed;

        if (sf::Keyboard::isKeyPressed(Controls::FORWARD)) {
            m_shape.move(changeVector.x, changeVector.y);
            m_moveSoundClock.restart();
        }
        if (sf::Keyboard::isKeyPressed(Controls::LEFT)) {
            m_shape.rotate(-0.5f);
            m_moveSoundClock.restart();
        }
        if (sf::Keyboard::isKeyPressed(Controls::BACK)) {
            m_shape.move(-changeVector.x, -changeVector.y);
            m_moveSoundClock.restart();
        }
        if (sf::Keyboard::isKeyPressed(Controls::RIGHT)) {
            m_shape.rotate(0.5f);
            m_moveSoundClock.restart();
        }

        PlayMovementSound();

        m_directionVector.angle = m_shape.getRotation();
    }

    [[nodiscard]] sf::Vector2f getTankCenterCoordinates() const {
        auto halfSizedTank = sf::Vector2f(m_shape.getSize().x / 2, m_shape.getSize().y / 2);
        return m_shape.getPosition() - halfSizedTank + m_shape.getOrigin();
    }

    [[nodiscard]] PolarVector getDirectionVector() const {
        return m_directionVector;
    }

private:
    sf::Music m_tankMovementSound;

    sf::Clock m_moveSoundClock;

    sf::RectangleShape m_shape;

    sf::Texture m_texture;

    PolarVector m_directionVector = {1.0f, 0.0f};
};