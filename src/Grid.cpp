#include "lib/Grid.hpp"
#include "lib/Camera.hpp"

Grid::Grid( std::string name ) :
        mName( name )
        , mGrid()
        , mTileSize( TILE_SIZE )
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

void Grid::render( sf::RenderTarget& target, sf::Time dt, sf::Vector2u windowSize, const Camera* camera ) const
{
    // Get the visible screen space
    sf::FloatRect screen(
            camera->getPosition().x - windowSize.x / (2.f * camera->getZoom()) + camera->getOffset().x,
            camera->getPosition().y - windowSize.y / (2.f * camera->getZoom()) + camera->getOffset().y,
            windowSize.x / camera->getZoom() + 16.f, // +16.f to adjust for window borders (probably)
            windowSize.y / camera->getZoom() + 16.f //  +16.f to adjust for window borders (probably
            // TODO: Verify why we need the 16.f
    );

    // Draw all objects in the grid
    for ( std::map<std::string, entPtr>::const_iterator it = mGrid.begin(); it != mGrid.end(); ++it )
    {
        // Get the object space
        sf::FloatRect object( it->second->getPosition(), it->second->getSize() );

        // Render the object only if it lies within our screen space
        if ( screen.intersects( object ) )
        {
            it->second->render( target, dt );
        }
    }
}

void Grid::update( sf::Time dt )
{
    for ( std::map<std::string, entPtr>::const_iterator it = mGrid.begin(); it != mGrid.end(); ++it )
    {
        it->second->update( dt );
    }
}

std::string Grid::getName() const
{
    return mName;
}

void Grid::setName( std::string name )
{
    mName = name;
}
