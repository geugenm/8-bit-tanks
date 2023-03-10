#pragma once

#include "SFML/Graphics.hpp"

class Cursor {
public:
    Cursor() {
        setTexture("resources/cursor/attack.png");
        buildSprite();
    }

    void setPosition(const sf::Vector2f &position) {
        m_sprite.setPosition(position);
    }

    [[nodiscard]] sf::Sprite getSprite() const {
        return m_sprite;
    }

private:
    void setTexture(const std::string_view & path) {
        if (!m_texture.loadFromFile(path.data())) {
            LOG(ERROR) << "Invalid cursor sprite: " << path;
            return;
        }
    }

    void buildSprite() {
        const sf::Vector2f halfOfTheTexture(m_texture.getSize() / 2u);

        m_sprite.setOrigin(halfOfTheTexture);
        m_sprite.setScale(0.015f, 0.015f);
        m_sprite.setTexture(m_texture);
    }

private:
    sf::Sprite m_sprite;

    sf::Texture m_texture;
};