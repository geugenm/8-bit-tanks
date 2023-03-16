#include "entity/Projectile.h"
#include "easylogging++.h"

Projectile::Projectile(const sf::Vector2f &launch, const sf::Vector2f &target) : m_targetPosition(target), m_launchPosition(launch) {
    createShapeObject(launch);

    setSpeed(kDefaultProjectileSpeed);
}

void Projectile::updatePosition() {
    m_projectileShape.setPosition(m_projectileShape.getPosition() + m_velocity * m_movementClock.getElapsedTime().asSeconds());
    m_movementClock.restart();
}

bool Projectile::isWithinScreenBounds() const {
    const bool widthCondition =
            getPosition().x < 0.0f || getPosition().x > Configuration::MainWindow::WIDTH;
    const bool heightCondition =
            getPosition().y < 0.0f || getPosition().y > Configuration::MainWindow::HEIGHT;

    if (widthCondition || heightCondition) {
        return false;
    }

    return true;
}

sf::Vector2f Projectile::getPosition() const {
    return m_projectileShape.getPosition();
}

sf::RectangleShape &Projectile::getShapeObject() {
    return m_projectileShape;
}

void Projectile::playShotSound() {
    if (m_projectileSound.getStatus() == sf::SoundSource::Playing) {
        return;
    }

    m_projectileSound.stop();

    m_projectileSound.play();
}

void Projectile::setSpeed(const float &speed) {
    if (speed < 0.0f) {
        throw std::invalid_argument("Invalid projectile speed given");
    }

    const float dx = m_targetPosition.x - m_launchPosition.x;
    const float dy = m_targetPosition.y - m_launchPosition.y;
    const float length = std::sqrt(dx * dx + dy * dy);
    m_velocity = sf::Vector2f(dx / length * speed, dy / length * speed);
}

void Projectile::setSound(const std::string_view &path) {
    if (m_soundBuffer.loadFromFile(path.data()) == false) {
        LOG(ERROR) << "Sound file is not found" << path;
        return;
    }

    m_projectileSound.setBuffer(m_soundBuffer);
}

void Projectile::createShapeObject(const sf::Vector2f &shapePosition) {
    m_projectileShape.setSize(sf::Vector2f(10.0f, 10.0f));
    m_projectileShape.setFillColor(sf::Color::Red);
    m_projectileShape.setPosition(shapePosition.x, shapePosition.y);
}

Bullet::Bullet(const sf::Vector2f &launch, const sf::Vector2f &target) : Projectile(launch, target) {
    setSound(Configuration::Sounds::BULLET_OUT);

    setSpeed(kDefaultSpeed);
    playShotSound();
}

Shell::Shell(const sf::Vector2f &launch, const sf::Vector2f &target) : Projectile(launch, target) {
    setSound(Configuration::Sounds::SHELL_OUT);

    setSpeed(kDefaultSpeed);
    playShotSound();
}
