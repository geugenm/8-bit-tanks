#pragma once

#include "SFML/Graphics.hpp"

class Cursor {
public:
    Cursor();

    void drawOn(sf::RenderWindow & window) {
        setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        window.draw(m_sprite);
    }

private:
    void setPosition(const sf::Vector2f &position);

    void setTexture(const std::string_view & path);

    void buildSprite();


    sf::Sprite m_sprite;

    sf::Texture m_texture;
};