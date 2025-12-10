#include "Game.h"
#include <algorithm>
#include <iostream>

Game::Game() :
    m_paletka({ 400.f, 560.f }, { 200.f, 20.f }, { 400.f, 0.f }),
    m_pilka({ 400.f, 300.f }, 15.f, { -480.f, -480.f })
{
    initBricks();
}

void Game::initBricks()
{
    const int SZER = 800;
    const int KOLUMNY = 4;
    const int WIERSZE = 2;
    const float szerBloku = 120.f;
    const float wysBloku = 30.f;
    const float odstep = 40.f;

    float startX = (SZER - (KOLUMNY * szerBloku + (KOLUMNY - 1) * odstep)) / 2.f;
    float startY = 80.f;

    for (int y = 0; y < WIERSZE; y++) {
        for (int x = 0; x < KOLUMNY; x++) {
            int zycie = 3;
            float posX = startX + x * (szerBloku + odstep);
            float posY = startY + y * (wysBloku + 25.f);
            m_bloki.emplace_back(sf::Vector2f(posX, posY),
                sf::Vector2f(szerBloku, wysBloku),
                zycie);
        }
    }
}

void Game::update(sf::Time dt, sf::Vector2u windowSize)
{
    const float SZER = (float)windowSize.x;
    const float WYS = (float)windowSize.y;

    m_paletka.ruch(dt, { SZER, WYS });
    m_pilka.ruch(dt, { SZER, WYS }, m_paletka);

    for (auto& b : m_bloki)
    {
        if (!b.czyZniszczony() &&
            m_pilka.getGlobalBounds().intersects(b.getGlobalBounds()))
        {
            b.trafienie();
            m_pilka.odbijY();
        }
    }

    m_bloki.erase(
        std::remove_if(m_bloki.begin(), m_bloki.end(),
            [](Brick& b) { return b.czyZniszczony(); }),
        m_bloki.end()
    );

    if (m_pilka.getY() - m_pilka.getRadius() > WYS)
    {
        std::cout << "MISS! KONIEC GRY\n";
    }
}

void Game::render(sf::RenderTarget& target)
{
    m_paletka.draw(target);
    m_pilka.draw(target);

    for (auto& b : m_bloki)
        b.draw(target);
}
