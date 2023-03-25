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
    void loadMovementSound(const std::string_view &path);

    void loadTexture(const std::string_view &path);

    void playMovementSound();

    void buildSprite();

    float m_movementSpeed = kDefaultMovementSpeed;
    float m_rotationSpeed = kDefaultRotationSpeed;

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    sf::Sound m_movementSound;

    sf::SoundBuffer m_movementSoundBuffer;

    PolarVector m_facingDirection = {1.0f, 0.0f};

    bool m_wasMoved = false;
};