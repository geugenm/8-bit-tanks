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
    }

    void update(const sf::Vector2f & mousePosition, const sf::Vector2f & position) {
        m_turretShape.setPosition(position);

        // Calculate the angle between the turret and the mouse cursor
        float dx = mousePosition.x - getPosition().x;
        float dy = mousePosition.y - getPosition().y;
        float angle = std::atan2(dy, dx) * 180.0f / static_cast<float>(M_PI);

        // Rotate the turret to face the mouse cursor
        m_turretShape.setRotation(angle);
        m_directionVector.angle = angle;
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(m_turretShape);
    }

    [[nodiscard]] sf::Vector2f getPosition() const {
        return m_turretShape.getPosition();
    }

    void setPosition(const sf::Vector2f &position) {
        m_turretShape.setPosition(position);
    }

    [[nodiscard]] sf::RectangleShape & getShape() {
        return m_turretShape;
    }

    [[nodiscard]] PolarVector getDirectionVector() const {
        return m_directionVector;
    }

private:
    PolarVector m_directionVector = {1.0f, 0.0f};

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    sf::RectangleShape m_turretShape;
};