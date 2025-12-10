#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct BlockData {
    float x, y;
    int hp;
};

class Paddle;
class Ball;
class Brick;

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    GameState() = default;

    void capture(const Paddle& p, const Ball& b, const std::vector<Brick>& bloki);

    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);

    void apply(Paddle& p, Ball& b, std::vector<Brick>& bloki);
};
