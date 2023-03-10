#include <cmath>
#include <Config.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Texture.hpp>

class Projectile {
public:
    explicit Projectile(const sf::Vector2f &launch, const sf::Vector2f &target) : m_target(target), m_start(launch) {
        buildShape(launch);

        setBulletSpeed(DEFAULT_PROJECTILE_SPEED);
    }


    void update() {
        m_shape.setPosition(m_shape.getPosition() + m_velocity * m_clock.getElapsedTime().asSeconds());
        m_clock.restart();
    }

    [[nodiscard]] bool isOnTheScreen() const {
        const bool widthCondition =
                getShapePosition().x < 0.0f || getShapePosition().x > Configuration::MainWindow::WIDTH;
        const bool heightCondition =
                getShapePosition().y < 0.0f || getShapePosition().y > Configuration::MainWindow::HEIGHT;

        if (widthCondition || heightCondition) {
            return false;
        }

        return true;
    }

    [[nodiscard]] sf::Vector2f getShapePosition() const {
        return m_shape.getPosition();
    }

    sf::RectangleShape &getShape() {
        return m_shape;
    }

    [[nodiscard]] float getBulletSpeed() const {
        return m_bulletSpeed;
    }

    void playSound() {
        static sf::Sound sound;
        sound.setBuffer(m_buffer);
        sound.play();
    }

    virtual ~Projectile() = default;

public:
    constexpr static float DEFAULT_PROJECTILE_SPEED = 10.0f;

protected:
    void setBulletSpeed(const float &speed) {
        if (speed <= 0.0f) {
            throw std::invalid_argument("Invalid projectile m_speed given");
        }

        const float dx = m_target.x - m_start.x;
        const float dy = m_target.y - m_start.y;
        const float length = std::sqrt(dx * dx + dy * dy);
        m_velocity = sf::Vector2f(dx / length * speed, dy / length * speed);

        m_bulletSpeed = speed;
    }

    void setSound(const std::string_view &path) {
        if (m_buffer.loadFromFile(path.data()) == false) {
            LOG(INFO) << "Sound file is not found" << path;
        }
        m_soundPath = path;
    }

    void setTexture(const std::string_view &path) {
        if (m_texture.loadFromFile(path.data()) == false) {
            LOG(INFO) << "Sound file is not found" << path;
        }
        m_shape.setTexture(&m_texture);

        m_texturePath = path;
    }

    void buildShape(const sf::Vector2f &shapePosition) {
        m_shape.setSize(sf::Vector2f(10.0f, 10.0f));
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setPosition(shapePosition.x, shapePosition.y);
    }

private:
    sf::RectangleShape m_shape;

    sf::Texture m_texture;
    std::string_view m_texturePath = "";

    sf::SoundBuffer m_buffer;
    std::string_view m_soundPath = "";

    sf::Clock m_clock;

    sf::Vector2f m_velocity;

    sf::Vector2f m_target;
    sf::Vector2f m_start;

    float m_bulletSpeed = DEFAULT_PROJECTILE_SPEED;
};


class Bullet final : public Projectile {
public:
    Bullet(const sf::Vector2f &launch, const sf::Vector2f &target) : Projectile(launch, target) {
        setSound("resources/Wav/mini_gun2.wav");

        setBulletSpeed(DEFAULT_SPEED);
    }

public:
    constexpr static float DEFAULT_SPEED = 1000.0f;
};

class Shell final : public Projectile {
public:
    Shell(const sf::Vector2f &launch, const sf::Vector2f &target) : Projectile(launch, target) {
        setSound("resources/Wav/explosion.wav");

        setBulletSpeed(DEFAULT_SPEED);
    }

public:
    constexpr static float DEFAULT_SPEED = 500.0f;
};




