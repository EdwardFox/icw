#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player();

        void handleEvent(const sf::Event& event);
        void handleRealtimeInput();
    private:
        
};

#endif
