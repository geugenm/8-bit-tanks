#include "Cursor.h"
#include "Config.h"
#include "easylogging++.h"

Cursor::Cursor() {
    loadTexture(Configuration::Textures::CURSOR);
    buildSprite();
}

void Cursor::setPosition(const sf::Vector2f &position) {
    m_sprite.setPosition(position);
}

sf::Sprite Cursor::getSprite() const {
    return m_sprite;
}

void Cursor::loadTexture(const std::string_view &path) {
    if (m_texture.loadFromFile(path.data()) == false) {
        LOG(ERROR) << "Invalid cursor sprite: " << path;
        return;
    }
}

void Cursor::buildSprite() {
    const sf::Vector2f textureScale(0.015f, 0.015f);
    const sf::Vector2f halfOfTheTexture(m_texture.getSize() / 2u);

    m_sprite.setOrigin(halfOfTheTexture);
    m_sprite.setScale(textureScale);
    m_sprite.setTexture(m_texture);
}
