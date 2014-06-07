#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include "Player.hpp"
#include "World.hpp"

class Game
{
    public:
        Game(sf::Vector2i size, std::string title);

        void processEvents();
        void render(sf::Time dt);
        void update(sf::Time dt);
        void run();

    private:
        sf::RenderWindow mWindow;
        sf::Time mTimePerFrame;
        Player mPlayer;
        World mWorld;
};

#endif
