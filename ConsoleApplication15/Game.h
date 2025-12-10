#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Pilka.h"
#include "Brick.h"

class Game {
public:
    Game();

    void update(sf::Time dt, sf::Vector2u windowSize);
    void render(sf::RenderTarget& target);

    Paddle& getPaddle() { return m_paletka; }
    Ball& getBall() { return m_pilka; }
    std::vector<Brick>& getBricks() { return m_bloki; }

private:
    Paddle m_paletka;
    Ball m_pilka;
    std::vector<Brick> m_bloki;

    void initBricks();
};
