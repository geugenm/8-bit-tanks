#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MovementVectors.h"

class Hull {
public:
    constexpr static float kDefaultMovementSpeed = 1.0f;
    constexpr static float kDefaultRotationSpeed = 0.5f;
    constexpr static float kSpriteScale = 2.0f;

    Hull();

    [[nodiscard]] sf::Sprite getSprite() const;

    void handlePlayerInputs();

private:
    void loadTexture(const std::string_view &path);

    void buildSprite();

    float m_movementSpeed = kDefaultMovementSpeed;
    float m_rotationSpeed = kDefaultRotationSpeed;

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    PolarVector m_facingDirection = {1.0f, 0.0f};

    bool m_wasMoved = false;
};