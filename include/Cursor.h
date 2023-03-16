#pragma once

#include "SFML/Graphics.hpp"

class Cursor {
public:
    Cursor();

    void setPosition(const sf::Vector2f &position);

    [[nodiscard]] sf::Sprite getSprite() const;

private:
    void loadTexture(const std::string_view & path);

    void buildSprite();

private:
    sf::Sprite m_sprite;

    sf::Texture m_texture;
};