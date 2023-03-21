#include <SFML/Graphics.hpp>
#include <cmath>

#include "entity/Hull.h"
#include "entity/Turret.h"
#include "Config.h"

#include "easylogging++.h"


Turret::Turret(const Hull &hull, const sf::Window &window) : kAttachedHull(hull), kAttachedWindow(window) {
    setTexture(Configuration::Textures::TURRET);
    buildSprite();

    setRotationSound(Configuration::Sounds::TURRET_ROTATE);
}

void Turret::updateRotation() {
    m_sprite.setPosition(kAttachedHull.getSprite().getPosition());

    // Calculate the angle between the turret and the mouse cursor
    const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(kAttachedWindow));
    const sf::Vector2f delta(mousePosition - getPosition());
    const float angle = std::atan2(delta.y, delta.x) * 180.0f / static_cast<float>(3.14);

    m_isRotating = m_directionVector.angle != angle;

    rotate(angle);
    playRotationSound();
}

void Turret::draw(sf::RenderWindow &window) const {
    window.draw(m_sprite);
}

sf::Vector2f Turret::getMuzzlePosition() const {
    PolarVector vector = m_directionVector;
    vector.radius *= m_texture.getSize().x * m_sprite.getScale().x / 2.0f;
    return getPosition() + vector.getDecartVector();
}

sf::Vector2f Turret::getPosition() const {
    return m_sprite.getPosition();
}

sf::Sprite &Turret::getSprite() {
    return m_sprite;
}

void Turret::setTexture(const std::string_view &path) {
    if (m_texture.loadFromFile(path.data()) == false) {
        LOG(ERROR) << "Missing texture for turret: " << path;
        return;
    }

    m_sprite.setTexture(m_texture);
}

void Turret::playRotationSound() {
    if (m_isRotating == false) {
        m_rotateSound.stop();
        return;
    }

    if (m_rotateSound.getStatus() == sf::SoundSource::Playing) {
        return;
    }

    m_rotateSound.play();
}

void Turret::setRotationSound(const std::string_view &path) {
    if (m_rotateSoundBuffer.loadFromFile(path.data()) == false) {
        LOG(ERROR) << "Missing turret rotation sound file: " << path;
        return;
    }
    m_rotateSound.setBuffer(m_rotateSoundBuffer);
}

void Turret::rotate(const float &angle) {
    if (m_isRotating == false) {
        return;
    }

    m_sprite.setRotation(angle);

    m_directionVector.angle = angle;
}

void Turret::buildSprite() {
    m_sprite.setScale(Hull::kSpriteScale, Hull::kSpriteScale);
    m_sprite.setOrigin(sf::Vector2f(m_texture.getSize() / 2u));

    m_sprite.setPosition(kAttachedHull.getSprite().getPosition());
}
