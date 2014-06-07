#include "Game.hpp"

int main(int argc, char* argv[])
{
    sf::Vector2i size(800, 600);
    std::string title("Platformer");

    Game game(size, title);
    game.run();
    
    return 0;
}
