#include <SFML/Graphics.hpp>
#include <cmath>

#include "entity/tanks/parts/Hull.h"
#include "entity/tanks/parts/Turret.h"
#include "Config.h"

#include "easylogging++.h"


Turret::Turret(const Hull &hull) : kAttachedHull(hull) {
    setTexture(Configuration::Textures::TURRET);
    buildSprite();
}

void Turret::updateRotation(const sf::RenderWindow & window) {
    m_sprite.setPosition(kAttachedHull.getSprite().getPosition());

    // Calculate the angle between the turret and the mouse cursor
    const auto mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
    const sf::Vector2f delta(mousePosition - getPosition());
    const float angle = std::atan2(delta.y, delta.x) * 180.0f / static_cast<float>(3.14);

    rotate(angle);
}

void Turret::drawOn(sf::RenderWindow &window) {
    updateRotation(window);
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

void Turret::rotate(const float &angle) {
    if (angle == m_directionVector.angle) {
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

sf::Vector2f Turret::getDirectionVector() const {
    return m_directionVector.getDecartVector();
}
