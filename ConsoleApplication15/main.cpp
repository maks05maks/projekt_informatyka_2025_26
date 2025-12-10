#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "GameState.h"
#include <iostream>

enum class AppState {
    Menu,
    Playing,
    Scores,
    Exiting
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;

    AppState currentState = AppState::Menu;

    sf::Clock dtClock;

    while (window.isOpen())
    {
        sf::Time dt = dtClock.restart();
        sf::Event e;

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();

            if (currentState == AppState::Menu)
            {
                if (e.type == sf::Event::KeyPressed)
                {
                    if (e.key.code == sf::Keyboard::Up)    menu.przesunG();
                    if (e.key.code == sf::Keyboard::Down)  menu.przesunD();

                    if (e.key.code == sf::Keyboard::Enter)
                    {
                        if (menu.getSelectedItem() == 0) {
                            currentState = AppState::Playing;
                        }
                        else if (menu.getSelectedItem() == 1) {
                            GameState gs;
                            if (gs.loadFromFile("zapis.txt")) {
                                gs.apply(game.getPaddle(), game.getBall(), game.getBricks());
                                currentState = AppState::Playing;
                            }
                            else {
                                std::cout << "Blad wczytywania!\n";
                            }
                        }
                        else if (menu.getSelectedItem() == 2) {
                            currentState = AppState::Scores;
                        }
                        else if (menu.getSelectedItem() == 3) {
                            window.close();
                        }
                    }


                }
            }

            if (currentState == AppState::Playing)
            {
                if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::F5)
                {
                    GameState gs;
                    gs.capture(game.getPaddle(), game.getBall(), game.getBricks());
                    gs.saveToFile("zapis.txt");
                    std::cout << "Gra zapisana!\n";
                }
            }

        }

        if (currentState == AppState::Playing)
            game.update(dt, window.getSize());

        window.clear();

        if (currentState == AppState::Menu)
            menu.draw(window);
        else if (currentState == AppState::Playing)
            game.render(window);


        window.display();
    }

    return 0;
}
