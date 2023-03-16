#include "entity/Hull.h"
#include "Config.h"
#include "easylogging++.h"

Hull::Hull() {
    loadTexture(Configuration::Textures::HULL);
    buildSprite();

    loadMovementSound(Configuration::Sounds::TANK_MOVEMENT);
}

sf::Sprite Hull::getSprite() const {
    return m_sprite;
}

void Hull::handlePlayerInputs() {
    const sf::Vector2f directionBeforeMovement = m_sprite.getPosition();
    const float rotationBeforeMovement = m_sprite.getRotation();

    const sf::Vector2f changeVector = m_facingDirection.getDecartVector() * m_movementSpeed;

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

    m_facingDirection.angle = m_sprite.getRotation();
    m_wasMoved =
            directionBeforeMovement != m_sprite.getPosition() || rotationBeforeMovement != m_sprite.getRotation();

    playMovementSound();
}

void Hull::loadMovementSound(const std::string_view &path) {
    if (m_movementSoundBuffer.loadFromFile(path.data()) == false) {
        LOG(ERROR) << "Hull movement sound is not found";
        return;
    }

    m_movementSound.setBuffer(m_movementSoundBuffer);
    m_movementSound.setLoop(true);
}

void Hull::loadTexture(const std::string_view &path) {
    if (m_texture.loadFromFile(path.data()) == false) {
        LOG(ERROR) << "Missing hull texture: " << path;
        return;
    }

    m_sprite.setTexture(m_texture);
}

void Hull::playMovementSound() {
    if (m_wasMoved == false) {
        m_movementSound.stop();
        return;
    }

    if (m_movementSound.getStatus() == sf::SoundSource::Playing) {
        return;
    }

    m_movementSound.play();
}

void Hull::buildSprite() {
    const sf::Vector2f startPosition(375.f, 275.f);

    m_sprite.setScale(kSpriteScale, kSpriteScale);
    m_sprite.setPosition(startPosition);
    m_sprite.setOrigin(sf::Vector2f(m_texture.getSize() / 2u));
}
