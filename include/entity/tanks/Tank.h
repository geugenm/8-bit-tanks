#pragma once

#include <SFML/Graphics.hpp>
#include "entity/projectiles/Projectile.h"

#include "parts/Hull.h"
#include "parts/Turret.h"

#include "entity/Entity.h"

#include <memory>
#include <deque>

class Tank : public Entity {
public:
    void drawOn(sf::RenderWindow &window) {
        m_hull->drawOn(window);
        m_turret->drawOn(window);

        for (const auto &projectile: m_projectiles) {
            projectile->drawOn(window);
        }

        shoot();
    }

    virtual ~Tank() = default;

protected:
    virtual void shoot() = 0;

    explicit Tank() {
        m_hull = std::make_unique<Hull>();
        m_turret = std::make_unique<Turret>(*m_hull);
    }

    void setHullTexture(const std::string_view &path) {
        m_hull->setTexture(path);
    }

    void setTurretTexture(const std::string_view &path) {
        m_turret->setTexture(path);
    }

    [[nodiscard]] std::deque<std::unique_ptr<Projectile>> &getProjectiles() {
        return m_projectiles;
    }

    [[nodiscard]] Turret getTurret() const {
        return *m_turret;
    }

    [[nodiscard]] Hull getHull() const {
        return *m_hull;
    }

private:
    std::unique_ptr<Hull> m_hull;
    std::unique_ptr<Turret> m_turret;

    std::deque<std::unique_ptr<Projectile>> m_projectiles;
};


class KV1 final : public Tank {
public:
    static constexpr float kMainWeaponSecondsToReload = 1.0f;
    static constexpr float kAltWeaponSecondsToReload = 0.15f;

    explicit KV1() {
        setHullTexture(Configuration::Textures::HULL);
        setTurretTexture(Configuration::Textures::TURRET);
    }

    ~KV1() override = default;

private:
    void shoot() override {
        if (sf::Mouse::isButtonPressed(Configuration::Controls::MAIN_WEAPON)) {
            if (m_shellClock.getElapsedTime().asSeconds() > kMainWeaponSecondsToReload) {
                getProjectiles().push_front(std::make_unique<Shell>(getTurret()));
                m_shellClock.restart();
            }
        }

        if (sf::Mouse::isButtonPressed(Configuration::Controls::ALTERNATIVE_WEAPON)) {
            if (m_bulletClock.getElapsedTime().asSeconds() > kAltWeaponSecondsToReload) {
                getProjectiles().push_front(std::make_unique<Bullet>(getTurret()));
                m_bulletClock.restart();
            }
        }

        while (!getProjectiles().empty() && !getProjectiles().front()->isWithinScreenBounds()) {
            getProjectiles().front().reset();
            getProjectiles().pop_front();
        }
    }

private:
    sf::Clock m_shellClock;
    sf::Clock m_bulletClock;
};