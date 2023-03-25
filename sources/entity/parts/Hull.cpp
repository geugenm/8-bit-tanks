#include "entity/tanks/parts/Hull.h"
#include "Config.h"
#include "easylogging++.h"

Hull::Hull() {
    setTexture(Configuration::Textures::HULL);
}

void Hull::updatePosition() {
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
}

void Hull::setTexture(const std::string_view &path) {
    if (m_texture.loadFromFile(path.data()) == false) {
        LOG(ERROR) << "Missing hull texture: " << path;
        return;
    }

    m_sprite.setTexture(m_texture);
    buildSprite();
}

void Hull::buildSprite() {
    const sf::Vector2f startPosition(375.f, 275.f);

    m_sprite.setScale(kSpriteScale, kSpriteScale);
    m_sprite.setPosition(startPosition);
    m_sprite.setOrigin(sf::Vector2f(m_texture.getSize() / 2u));
}
