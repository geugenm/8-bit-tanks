#pragma once

#include "SFML/Graphics.hpp"
#include <cmath>
#include "MovementVectors.h"

class Turret {
public:
    explicit Turret(const sf::Vector2f & position) {
        if (!m_texture.loadFromFile("resources/textures/turret.png")) {
            throw std::invalid_argument("No texture for turret");
        }

        m_turretShape.setSize((sf::Vector2f(65, 35)));
        m_turretShape.setOrigin(m_turretShape.getSize() / 2.f);

        m_turretShape.setTexture(&m_texture);

        m_turretShape.setPosition(position);

        if (m_rotateSound.openFromFile(m_rotateSoundFilePath.data())) {
            LOG(ERROR) << m_rotateSoundFilePath.data() << " is not found";
        }
    }

    void update(const sf::Vector2f & mousePosition, const sf::Vector2f & position) {
        m_turretShape.setPosition(position);

        // Calculate the angle between the turret and the mouse cursor
        float dx = mousePosition.x - getPosition().x;
        float dy = mousePosition.y - getPosition().y;
        float angle = std::atan2(dy, dx) * 180.0f / static_cast<float>(M_PI);

        if (m_directionVector.angle == angle) {
            return;
        }
        
        // Rotate the turret to face the mouse cursor
        m_turretShape.setRotation(angle);
        m_directionVector.angle = angle;
        playSound();
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(m_turretShape);
    }

    [[nodiscard]] sf::Vector2f getPosition() const {
        return m_turretShape.getPosition();
    }

    [[nodiscard]] sf::RectangleShape & getShape() {
        return m_turretShape;
    }

    [[nodiscard]] PolarVector getDirectionVector() const {
        return m_directionVector;
    }

    void playSound() {
        if (m_rotateSound.getStatus() == sf::SoundSource::Playing) {
            return;
        }
        m_rotateSound.stop();
        m_rotateSound.play();
    }

private:
    PolarVector m_directionVector = {1.0f, 0.0f};

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    std::string_view m_rotateSoundFilePath = "resources/Wav/tank_tower.wav";
    sf::Music m_rotateSound;

    sf::RectangleShape m_turretShape;
};