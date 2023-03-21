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