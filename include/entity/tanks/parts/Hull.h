#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MovementVectors.h"
#include "entity/Entity.h"


class Hull final: public Entity {
public:
    constexpr static float kDefaultMovementSpeed = 1.0f;
    constexpr static float kDefaultRotationSpeed = 0.5f;
    constexpr static float kSpriteScale = 2.0f;

    Hull();

    void drawOn(sf::RenderWindow & window) {
        window.draw(m_sprite);
        updatePosition();
    }

    [[nodiscard]] sf::Sprite getSprite() const {
        return m_sprite;
    }

    void setTexture(const std::string_view &path);

private:
    void updatePosition();

    void buildSprite();

    float m_movementSpeed = kDefaultMovementSpeed;
    float m_rotationSpeed = kDefaultRotationSpeed;

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    PolarVector m_facingDirection = {1.0f, 0.0f};
};