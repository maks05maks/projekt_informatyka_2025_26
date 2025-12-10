#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
class Ball {
private:
    sf::CircleShape m_shape;
    sf::Vector2f velocity;
public:
    Ball(sf::Vector2f startPos, float radius, sf::Vector2f startVel)
        : velocity(startVel)
    {
        m_shape.setRadius(radius);
        m_shape.setOrigin(radius, radius);
        m_shape.setPosition(startPos);
        m_shape.setFillColor(sf::Color::Cyan);
    }
    void odbijY() {
        velocity.y = -velocity.y;
    }
    void odbijX() {
        velocity.x = -velocity.x;
    }
    void ruch(sf::Time dt, sf::Vector2f windowWH, Paddle& pad) {
        m_shape.move(velocity * dt.asSeconds());
        float x = m_shape.getPosition().x;
        float y = m_shape.getPosition().y;
        float r = m_shape.getRadius();
        if (x - r < 0) { velocity.x = -velocity.x; m_shape.setPosition(r, y); }
        if (x + r > windowWH.x) { velocity.x = -velocity.x; m_shape.setPosition(windowWH.x - r, y); }
        if (y - r < 0) { velocity.y = -velocity.y; m_shape.setPosition(x, r); }
        if (m_shape.getGlobalBounds().intersects(pad.getGlobalBounds())) {
            velocity.y = -abs(velocity.y);
            m_shape.setPosition(x, pad.getGlobalBounds().top - r);
        }
    }
    float getX() const { return m_shape.getPosition().x; }
    float getY() const { return m_shape.getPosition().y; }
    float getVx() const { return velocity.x; }
    float getVy() const { return velocity.y; }
    float getRadius() const { return m_shape.getRadius(); }
    sf::FloatRect getGlobalBounds() const { return m_shape.getGlobalBounds(); }
    void draw(sf::RenderTarget& w) {
        w.draw(m_shape);
    }

    void reset(sf::Vector2f pos, sf::Vector2f vel) {
        m_shape.setPosition(pos);
        velocity = vel;
    }

};