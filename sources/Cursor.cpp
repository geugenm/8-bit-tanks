#include "Cursor.h"
#include "Config.h"
#include "easylogging++.h"

Cursor::Cursor() {
    setTexture(Configuration::Textures::CURSOR);
}

void Cursor::setPosition(const sf::Vector2f &position) {
    m_sprite.setPosition(position);
}

void Cursor::setTexture(const std::string_view &path) {
    if (m_texture.loadFromFile(path.data()) == false) {
        LOG(ERROR) << "Invalid cursor sprite: " << path;
        return;
    }

    buildSprite();
}

void Cursor::buildSprite() {
    const sf::Vector2f textureScale(0.015f, 0.015f);
    const sf::Vector2f halfOfTheTexture(m_texture.getSize() / 2u);

    m_sprite.setOrigin(halfOfTheTexture);
    m_sprite.setScale(textureScale);
    m_sprite.setTexture(m_texture);
}

void Cursor::drawOn(sf::RenderWindow &window) {
    window.draw(m_sprite);

    setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
}
