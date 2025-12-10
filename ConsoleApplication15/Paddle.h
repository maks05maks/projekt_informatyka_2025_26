#pragma once
#include <SFML/Graphics.hpp>
class Paddle {
private:
    sf::RectangleShape m_shape;
    sf::Vector2f velocity;   // px/s
public:
    Paddle(sf::Vector2f startPos, sf::Vector2f rozmiar, sf::Vector2f startVel)
        : velocity(startVel)
    {
        m_shape.setSize(rozmiar);
        m_shape.setOrigin(rozmiar.x / 2.f, rozmiar.y / 2.f);
        m_shape.setPosition(startPos);
        m_shape.setFillColor(sf::Color::White);
    }
    void ruch(sf::Time dt, sf::Vector2f windowWH) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_shape.move(-velocity.x * dt.asSeconds(), 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_shape.move(velocity.x * dt.asSeconds(), 0.f);
        }
        if (m_shape.getPosition().x - m_shape.getSize().x / 2.f < 0)
            m_shape.setPosition(m_shape.getSize().x / 2.f, m_shape.getPosition().y);
        if (m_shape.getPosition().x + m_shape.getSize().x / 2.f > windowWH.x)
            m_shape.setPosition(windowWH.x - m_shape.getSize().x / 2.f, m_shape.getPosition().y);
    }
    void draw(sf::RenderTarget& window) {
        window.draw(m_shape);
    }
    sf::FloatRect getGlobalBounds() const {
        return m_shape.getGlobalBounds();
    }

    void setPosition(sf::Vector2f pos) { m_shape.setPosition(pos); }

};