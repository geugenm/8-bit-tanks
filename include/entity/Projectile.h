#include <cmath>
#include <Config.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "entity/Turret.h"

class Projectile {
public:
    void updatePosition();

    [[nodiscard]] bool isWithinScreenBounds() const;

    [[nodiscard]] sf::Vector2f getPosition() const;

    sf::RectangleShape &getShapeObject();

    virtual ~Projectile() = default;

protected:
    explicit Projectile(const sf::Vector2f &launch, const sf::Vector2f &target);

    void setSpeed(const float &speed);

    void createShapeObject(const sf::Vector2f &shapePosition);

private:
    sf::RectangleShape m_projectileShape;

    sf::Clock m_movementClock;

    sf::Vector2f m_velocity;

    sf::Vector2f m_targetPosition;
    sf::Vector2f m_launchPosition;
};


class Bullet final : public Projectile {
public:
    constexpr static float kDefaultSpeed = 1000.0f;

    explicit Bullet(const sf::Vector2f &launch, const sf::Vector2f &target);

    explicit Bullet(const Turret &turret) : Bullet(turret.getPosition(),
                                                   turret.getMuzzlePosition() + turret.getDirectionVector()) {
    }
};

class Shell final : public Projectile {
public:
    constexpr static float kDefaultSpeed = 500.0f;

    Shell(const sf::Vector2f &launch, const sf::Vector2f &target);

    explicit Shell(const Turret &turret) : Shell(turret.getMuzzlePosition(),
                                                   turret.getMuzzlePosition() + turret.getDirectionVector()) {
    }
};




