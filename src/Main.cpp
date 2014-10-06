#include "lib/Game.hpp"

int main( int argc, char* argv[] )
{
    sf::Vector2i size( 1300, 700 );
    std::string title( "Platformer" );

    Game game( size, title );
    game.run();

    return 0;
}
