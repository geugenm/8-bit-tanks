#pragma once

#include <SFML/Graphics.hpp>

class Entity {
public:
    virtual void drawOn(sf::RenderWindow & window) = 0;

    virtual ~Entity() = default;
};