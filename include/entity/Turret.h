#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "MovementVectors.h"
#include "Hull.h"

class Turret {
public:
    const Hull & kAttachedHull;

    const sf::Window & kAttachedWindow;


    explicit Turret(const Hull & hull, const sf::Window & window) : kAttachedHull(hull), kAttachedWindow(window) {
        setTexture("resources/textures/turret.png");
        buildSprite();

        setSound("resources/Wav/tank_tower.wav");
    }

    void update() {
        m_sprite.setPosition(kAttachedHull.getSprite().getPosition());

        // Calculate the angle between the turret and the mouse cursor
        const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(kAttachedWindow));
        const sf::Vector2f delta(mousePosition - getPosition());
        const float angle = std::atan2(delta.y, delta.x) * 180.0f / static_cast<float>(M_PI);

        m_isRotating = m_directionVector.angle != angle;

        rotate(angle);
        playSound();
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(m_sprite);
    }

    [[nodiscard]] sf::Vector2f getMuzzlePosition() const {
        PolarVector vector = m_directionVector;
        vector.radius *= m_texture.getSize().x * m_sprite.getScale().x / 2.f;
        return getPosition() + vector.getDecartVector();
    }

    [[nodiscard]] sf::Vector2f getPosition() const {
        return m_sprite.getPosition();
    }

    [[nodiscard]] sf::Sprite & getSprite() {
        return m_sprite;
    }

private:
    void setTexture(const std::string_view & path) {
        if (!m_texture.loadFromFile(path.data())) {
            LOG(ERROR) << "Missing texture for turret: " << path;
            return;
        }

        m_sprite.setTexture(m_texture);
    }

    void playSound() {
        if (m_isRotating == false) {
            m_rotateSound.stop();
            return;
        }

        if (m_rotateSound.getStatus() == sf::SoundSource::Playing) {
            return;
        }

        m_rotateSound.stop();
        m_rotateSound.play();
    }

    void buildSprite() {
        m_sprite.setScale(Hull::kSpriteScale, Hull::kSpriteScale);
        m_sprite.setOrigin(sf::Vector2f(m_texture.getSize() / 2u));

        m_sprite.setPosition(kAttachedHull.getSprite().getPosition());
    }

    void setSound(const std::string_view & path) {
        if (m_rotateSoundBuffer.loadFromFile(path.data())) {
            LOG(ERROR) << "Missing turret rotation sound file: " << path;
            return;
        }
        m_rotateSound.setBuffer(m_rotateSoundBuffer);
    }

    void rotate(const float & angle) {
        if (m_isRotating == false) {
            return;
        }

        m_sprite.setRotation(angle);

        m_directionVector.angle = angle;
    }

    PolarVector m_directionVector = {1.0f, 0.0f};

    sf::Texture m_texture;

    sf::SoundBuffer m_rotateSoundBuffer;

    sf::Sound m_rotateSound;

    bool m_isRotating = false;

    sf::Sprite m_sprite;
};