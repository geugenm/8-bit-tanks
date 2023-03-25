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
        update();
        shoot();

        window.draw(m_hull->getSprite());
        m_turret->show(window);

        for (const auto& projectile : m_projectiles) {
            window.draw(projectile->getShapeObject());
        }
    }

    virtual ~Tank() = default;

protected:
    void update() {
        m_hull->handlePlayerInputsAndMove();

        for (const auto& projectile : m_projectiles) {
            projectile->updatePosition();
        }
    }

    virtual void shoot() = 0;

    explicit Tank() {
        m_hull = std::make_unique<Hull>();
        m_turret = std::make_unique<Turret>(*m_hull);
    }

    void setHullTexture(const std::string_view & path) {
        m_hull->setTexture(path);
    }

    void setTurretTexture(const std::string_view & path) {
        m_turret->setTexture(path);
    }

    [[nodiscard]] std::deque<std::unique_ptr<Projectile>> & getProjectiles() {
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

class KV1 : public Tank {
public:
    explicit KV1() {
        setHullTexture(Configuration::Textures::HULL);
        setTurretTexture(Configuration::Textures::TURRET);
    }

    ~KV1() override = default;

private:
    void shoot() override {
        constexpr float mainWeaponReloadTime = 1.0f;
        if (sf::Mouse::isButtonPressed(Configuration::Controls::MAIN_WEAPON)) {
            if (m_shellClock.getElapsedTime().asSeconds() > mainWeaponReloadTime) {
                getProjectiles().push_front(std::make_unique<Shell>(getTurret()));
                m_shellClock.restart();
            }
        }

        constexpr float altWeaponReloadTime = 0.15f;
        if (sf::Mouse::isButtonPressed(Configuration::Controls::ALTERNATIVE_WEAPON)) {
            if (m_bulletClock.getElapsedTime().asSeconds() > altWeaponReloadTime) {
                getProjectiles().push_front(std::make_unique<Bullet>(getTurret()));
                m_bulletClock.restart();
            }
        }

        while (!getProjectiles().empty() && !getProjectiles().front()->isWithinScreenBounds()) {
            getProjectiles().front().reset();
            getProjectiles().pop_front();
        }

        for (const auto& projectile : getProjectiles()) {
            projectile->updatePosition();
        }
    }

private:
    sf::Clock m_shellClock;
    sf::Clock m_bulletClock;
};