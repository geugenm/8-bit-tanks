#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "MovementVectors.h"
#include "Hull.h"

class Turret {
public:
    explicit Turret(const Hull &hull, const sf::Window &window);

    void updateRotation();

    void draw(sf::RenderWindow &window) const;

    [[nodiscard]] sf::Vector2f getMuzzlePosition() const;

    [[nodiscard]] sf::Vector2f getPosition() const;

    [[nodiscard]] sf::Sprite &getSprite();

    [[nodiscard]] sf::Vector2f getDirectionVector() const {
        return m_directionVector.getDecartVector();
    }

private:
    void setTexture(const std::string_view &path);

    void buildSprite();

    void rotate(const float &angle);


    const Hull &kAttachedHull;

    const sf::Window &kAttachedWindow;

    PolarVector m_directionVector = {1.0f, 0.0f};

    sf::Texture m_texture;

    bool m_isRotating = false;

    sf::Sprite m_sprite;
};