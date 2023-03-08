#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>

struct PolarVector {
    [[nodiscard]] float getX() const {
        float radians = angle * (3.14159f / 180.0f);
        return radius * cos(radians);
    }

    [[nodiscard]] float getY() const {
        float radians = angle * (3.14159f / 180.0f);
        return radius * sin(radians);
    }

    [[nodiscard]] sf::Vector2f getDecartVector() const {
        return {getX(), getY()};
    }

    float radius = 1.0f;
    float angle = 0.0f;
};

class DirectionVector {
public:
    DirectionVector(const sf::Vector2f & start, const sf::Vector2f & end, const sf::Color & color = sf::Color::Red) {
        m_line = sf::VertexArray(sf::Lines, VECTOR_POINTS_AMOUNT);
        m_line[0].position = start;
        m_line[0].color = color;
        m_line[1].position = end;
        m_line[1].color = color;
    }

    [[nodiscard]] sf::VertexArray getShape() const {
        return m_line;
    }

public:
    constexpr static uint16_t VECTOR_POINTS_AMOUNT = 2;

private:
    sf::VertexArray m_line;
};