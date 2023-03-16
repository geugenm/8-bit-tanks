#include <cmath>
#include <Config.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Projectile {
public:
    constexpr static float kDefaultProjectileSpeed = 10.0f;


    explicit Projectile(const sf::Vector2f &launch, const sf::Vector2f &target);


    void updatePosition();

    [[nodiscard]] bool isWithinScreenBounds() const;

    [[nodiscard]] sf::Vector2f getPosition() const;

    sf::RectangleShape &getShapeObject();

    virtual ~Projectile() = default;

protected:
    void playShotSound();

    void setSpeed(const float &speed);

    void setSound(const std::string_view &path);

    void createShapeObject(const sf::Vector2f &shapePosition);

private:
    sf::RectangleShape m_projectileShape;

    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_projectileSound;

    sf::Clock m_movementClock;

    sf::Vector2f m_velocity;

    sf::Vector2f m_targetPosition;
    sf::Vector2f m_launchPosition;
};


class Bullet final : public Projectile {
public:
    constexpr static float kDefaultSpeed = 1000.0f;

    Bullet(const sf::Vector2f &launch, const sf::Vector2f &target);
};

class Shell final : public Projectile {
public:
    constexpr static float kDefaultSpeed = 500.0f;

    Shell(const sf::Vector2f &launch, const sf::Vector2f &target);
};




