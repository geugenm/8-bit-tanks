#pragma once

#include "SFML/Graphics.hpp"

class Cursor {
public:
    Cursor() {
        if (!m_texture.loadFromFile("resources/cursor/attack.png")) {
            throw std::invalid_argument("No texture for cursor given.");
        }

        m_shape = sf::CircleShape(20.0f);
        m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
        m_shape.setTexture(&m_texture);
    }

    void setPosition(const sf::Vector2f &position) {
        m_shape.setPosition(position);
    }

    [[nodiscard]] sf::CircleShape getShape() const {
        return m_shape;
    }

private:
    sf::CircleShape m_shape;

    sf::Texture m_texture;
};