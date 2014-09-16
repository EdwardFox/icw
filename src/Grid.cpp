#include "lib/Grid.hpp"

Grid::Grid() :
        mGrid()
        , mTileSize( TILE_SIZE*4 )
{

}

GameObject* const Grid::getTile( std::string key ) const
{
    try
    {
        return mGrid.at( key ).get();
    }
    catch ( const std::out_of_range& oor )
    {
        return nullptr;
    }
}

sf::Vector2i Grid::getGridPosition( sf::Vector2f position )
{
    int posX = ( int )(position.x / mTileSize) * mTileSize;
    int posY = ( int )(position.y / mTileSize) * mTileSize;

    return sf::Vector2i( posX, posY );
}

std::string Grid::getTileKeyByPosition( sf::Vector2f position )
{
    sf::Vector2i tilePos = this->getGridPosition( position );
    return std::to_string( ( int )tilePos.x ) + "_" + std::to_string( ( int )tilePos.y );
}

unsigned Grid::getTileSize() const
{
    return mTileSize;
}

void Grid::addTile( std::string key, GameObject* ent )
{
    mGrid.emplace( key, entPtr( ent ) );
}

void Grid::removeTile( std::string key )
{
    mGrid.erase( key );
}

void Grid::setTileSize( unsigned tileSize )
{
    mTileSize = tileSize;
}

void Grid::render( sf::RenderTarget& target, sf::Time dt ) const
{
    for ( std::map<std::string, entPtr>::const_iterator it = mGrid.begin(); it != mGrid.end(); ++it )
    {
        it->second->render( target, dt );
    }
}

void Grid::update( sf::Time dt )
{
    for ( std::map<std::string, entPtr>::const_iterator it = mGrid.begin(); it != mGrid.end(); ++it )
    {
        it->second->update( dt );
    }
}
