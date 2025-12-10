#pragma once
#include <SFML/Graphics.hpp>
#include <array>
class Brick {
private:
    int punktyZycia;
    bool jestZniszczony;
    sf::RectangleShape shape;
    static const std::array<sf::Color, 4> colorLUT;
public:
    Brick(sf::Vector2f pos, sf::Vector2f size, int L)
        : punktyZycia(L), jestZniszczony(false)
    {
        shape.setSize(size);
        shape.setPosition(pos);
        shape.setFillColor(colorLUT[L]);
    }
    void trafienie() {
        if (jestZniszczony) return;
        punktyZycia--;
        if (punktyZycia <= 0) {
            jestZniszczony = true;
        }
        else {
            shape.setFillColor(colorLUT[punktyZycia]);
        }
    }
    bool czyZniszczony() const { return jestZniszczony; }
    sf::FloatRect getGlobalBounds() const { return shape.getGlobalBounds(); }
    void draw(sf::RenderTarget& win) { win.draw(shape); }

    int getHP() const { return punktyZycia; }

};