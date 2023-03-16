#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "MovementVectors.h"
#include "Hull.h"

class Turret {
public:
    const Hull &kAttachedHull;

    const sf::Window &kAttachedWindow;


    explicit Turret(const Hull &hull, const sf::Window &window);

    void updateRotation();

    void draw(sf::RenderWindow &window) const;

    [[nodiscard]] sf::Vector2f getMuzzlePosition() const;

    [[nodiscard]] sf::Vector2f getPosition() const;

    [[nodiscard]] sf::Sprite &getSprite();

private:
    void setTexture(const std::string_view &path);

    void playRotationSound();

    void buildSprite();

    void setRotationSound(const std::string_view &path);

    void rotate(const float &angle);


    PolarVector m_directionVector = {1.0f, 0.0f};

    sf::Texture m_texture;

    sf::SoundBuffer m_rotateSoundBuffer;

    sf::Sound m_rotateSound;

    bool m_isRotating = false;

    sf::Sprite m_sprite;
};