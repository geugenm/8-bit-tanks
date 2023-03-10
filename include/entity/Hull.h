#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Hull {
public:
    constexpr static float kDefaultMovementSpeed = 1.0f;
    constexpr static float kDefaultRotationSpeed = 0.5f;
    constexpr static float kSpriteScale = 0.09f;

    Hull() {
        setTexture("resources/textures/tank.png");
        buildSprite();

        setSound("resources/Wav/tank_move.wav");
    }

    [[nodiscard]] sf::Sprite getSprite() const {
        return m_sprite;
    }

    void handleInputs() {
        const sf::Vector2f directionBeforeMovement = m_sprite.getPosition();
        const float rotationBeforeMovement = m_sprite.getRotation();

        const sf::Vector2f changeVector = m_directionVector.getDecartVector() * m_movementSpeed;

        if (sf::Keyboard::isKeyPressed(Configuration::Controls::FORWARD)) {
            m_sprite.move(changeVector.x, changeVector.y);
        }
        if (sf::Keyboard::isKeyPressed(Configuration::Controls::LEFT)) {
            m_sprite.rotate(-m_rotationSpeed);
        }
        if (sf::Keyboard::isKeyPressed(Configuration::Controls::BACK)) {
            m_sprite.move(-changeVector.x, -changeVector.y);
        }
        if (sf::Keyboard::isKeyPressed(Configuration::Controls::RIGHT)) {
            m_sprite.rotate(m_rotationSpeed);
        }

        m_directionVector.angle = m_sprite.getRotation();
        m_wasMoved = directionBeforeMovement != m_sprite.getPosition() || rotationBeforeMovement != m_sprite.getRotation();

        playMovementSound();
    }

private:
    void setSound(const std::string_view &path) {
        if (!m_movementSoundBuffer.loadFromFile(path.data())) {
            LOG(INFO) << "Hull movement sound is not found";
            return;
        }

        m_movementSound.setBuffer(m_movementSoundBuffer);
        m_movementSound.setLoop(true);
    }

    void setTexture(const std::string_view &path) {
        if (!m_texture.loadFromFile(path.data())) {
            LOG(ERROR) << "Missing hull texture: " << path;
            return;
        }

        m_sprite.setTexture(m_texture);
    }

    void playMovementSound() {
        if (!m_wasMoved) {
            m_movementSound.stop();
            return;
        }

        if (m_movementSound.getStatus() == sf::SoundSource::Playing) {
            return;
        }

        m_movementSound.play();
    }

    void buildSprite() {
        const sf::Vector2f startPosition(375.f, 275.f);

        m_sprite.setScale(kSpriteScale, kSpriteScale);
        m_sprite.setPosition(startPosition);
        m_sprite.setOrigin(sf::Vector2f(m_texture.getSize() / 2u));
    }

    float m_movementSpeed = kDefaultMovementSpeed;
    float m_rotationSpeed = kDefaultRotationSpeed;

    sf::Texture m_texture;

    sf::Sprite m_sprite;

    sf::Sound m_movementSound;

    sf::SoundBuffer m_movementSoundBuffer;

    PolarVector m_directionVector = {1.0f, 0.0f};

    bool m_wasMoved = false;
};