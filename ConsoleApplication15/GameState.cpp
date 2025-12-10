#include "GameState.h"
#include "Paddle.h"
#include "Pilka.h"
#include "Brick.h"
#include <fstream>

void GameState::capture(const Paddle& p, const Ball& b, const std::vector<Brick>& bloki)
{
    paddlePosition = p.getGlobalBounds().getPosition();
    ballPosition = { b.getX(), b.getY() };
    ballVelocity = { b.getVx(), b.getVy() };

    blocks.clear();
    for (const auto& block : bloki) {
        BlockData d;
        sf::FloatRect r = block.getGlobalBounds();
        d.x = r.left;
        d.y = r.top;
        d.hp = block.getHP();
        blocks.push_back(d);
    }
}

bool GameState::saveToFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (auto& b : blocks)
        file << b.x << " " << b.y << " " << b.hp << "\n";

    return true;
}

bool GameState::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string lab;
    file >> lab >> paddlePosition.x >> paddlePosition.y;
    file >> lab >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;

    int count;
    file >> lab >> count;

    blocks.clear();
    for (int i = 0; i < count; i++) {
        BlockData d;
        file >> d.x >> d.y >> d.hp;
        blocks.push_back(d);
    }

    return true;
}

void GameState::apply(Paddle& p, Ball& b, std::vector<Brick>& bloki)
{
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);

    bloki.clear();
    sf::Vector2f size(120.f, 30.f);

    for (auto& d : blocks)
        bloki.emplace_back(sf::Vector2f(d.x, d.y), size, d.hp);
}
