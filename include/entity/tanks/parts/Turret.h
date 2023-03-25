#pragma once

#include "entity/Entity.h"
#include <SFML/Graphics.hpp>
#include <cmath>

#include "MovementVectors.h"
#include "Hull.h"

class Turret final: public Entity {
public:
    const Hull &kAttachedHull;


    explicit Turret(const Hull &hull);

    ~Turret() override = default;



    void drawOn(sf::RenderWindow &window) override;

    [[nodiscard]] sf::Vector2f getMuzzlePosition() const;

    [[nodiscard]] sf::Vector2f getPosition() const;

    [[nodiscard]] sf::Sprite &getSprite();

    [[nodiscard]] sf::Vector2f getDirectionVector() const;

    void setTexture(const std::string_view &path);


private:
    void buildSprite();

    void rotate(const float &angle);

    void updateRotation(const sf::RenderWindow & window);

    PolarVector m_directionVector = {1.0f, 0.0f};

    sf::Texture m_texture;

    sf::Sprite m_sprite;
};