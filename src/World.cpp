#include <lib/gameobjects/Fireball.hpp>
#include <lib/components/HealthComponent.hpp>
#include <lib/components/SpawnerComponent.hpp>
#include <lib/gamestates/LostState.hpp>
#include "lib/World.hpp"
#include "lib/components/ActionComponent.hpp"
#include "lib/components/AnimationGraphicsComponent.hpp"
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/components/DefaultStateHandlerComponent.hpp"
#include "lib/components/PlayerInputComponent.hpp"
#include "lib/components/PlayerMovementComponent.hpp"
#include "lib/components/ProjectileAIComponent.hpp"
#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/components/TextureGraphicsComponent.hpp"
#include "lib/Game.hpp"

World::World() :
        mTextures()
        , mSounds()
        , mGrids()
        , mObjects()
        , mObjectsToCreate()
        , mPhysics( b2Vec2( 0.f, 9.8f ) )
        , mCamera()
        , mPlayer( nullptr )
        , mMap()
        , mWorldGrid( nullptr )
        , mListener()
        , mGameObjectFactory()
        , mSurvivalTimer()
        , mKillCount( 0 )
{
    /** Initialize textures (as long as the objects do not do it for themselves **/
    initializeTextures();

    initializeSounds();

    /** We need to set our custom contact listener **/
    mPhysics.SetContactListener( &mListener );

    /**
    * Load a test map and create the player.
    * TODO: Create proper user interface to allow choosing different maps
    */
//    this->loadMap( "media/maps/Temple.tmx" );

}

void World::render( sf::RenderTarget& target, sf::Time dt ) const
{
    mCamera.render( target, dt );

    /**
    * Render all layers (beginning with the backgrounds) until we have rendered
    * the world (collision) layer. Next render all dynamic game objects, followed
    * by the remaining layers (foreground). This guarantees proper ordering on the
    * z-axis.
    */
    for ( auto& grid : mGrids )
    {
        grid->render( target, dt, &mCamera );
        if ( grid->getName() == "World" )
        {
            for ( auto& object : mObjects )
            {
                object->render( target, dt );
            }

            if( mPlayer )
                mPlayer->render( target, dt );
        }
    }
}

void World::update( sf::Time dt, sf::Vector2u windowSize, Game* game )
{
    mPhysics.Step( dt.asSeconds(), 8, 3 );

    mCamera.update( dt, windowSize );

    for ( auto& grid : mGrids )
    {
        grid->update( dt );
    }

    /**
    * Custom loop to get the proper pointer after erasing an expired object.
    * In addition we need to delete the physics body explicitly after the
    * world step has happened. This means we have to do it right before
    * deleting the object itself.
    *
    * Deleting the body in the objects destructor is an option, though
    * upon terminating the game we run into a segfault which leads back
    * to deleting the body in the destructor. Might be a bug with box2d.
    * Needs further investigation.
    */
    auto i = mObjects.begin();
    while ( i != mObjects.end() )
    {
        GameObject* obj = i->get();

        obj->update( dt );
        if ( obj->isExpired() )
        {
            std::string name = i->get()->getName();
            IPhysicsComponent* boxComp = dynamic_cast<IPhysicsComponent*>(obj->getComponent( "PhysicsComponent" ));
            boxComp->destroyBody();
            i = mObjects.erase( i );

            if( name == "Player" )
            {
                game->changeState( new LostState( game, std::round(mSurvivalTimer.getElapsedTime().asSeconds()), mKillCount ) );
                return;
            }
            else if( name == "EnemyA" )
            {
                mKillCount++;
            }
        }
        else
        {
            ++i;
        }
    }

    /** Put all objects that were newly created into the objects vector and clear the creation-vector upon completion **/
    for ( auto& object : mObjectsToCreate )
    {
        mObjects.push_back( std::unique_ptr<GameObject>( std::move( object ) ) );
    }
    mObjectsToCreate.clear();
}

void World::loadMap( std::string path )
{
    mMap.load( path, mTextures );

    /** Create a grid for each layer **/
    for ( const auto layer : *mMap.getLayers() )
    {
        Grid* grid = new Grid( layer.name );

        /** Keep track of the world layer **/
        if ( layer.name == "World" )
            mWorldGrid = grid;

        /** Set tile size **/
        grid->setTileSize( mMap.getTileSize().x );

        /** Add each tile and its proper texture **/
        for ( int i = 0; i < layer.rows; ++i )
        {
            for ( int j = 0; j < layer.columns; ++j )
            {
                /**
                * Calculate the current tile position and get the associated gid
                *
                *   current row * maximum number of columns + current column
                */
                int gid = layer.gids.at( i * layer.columns + j );

                /** Proceed to the next tile if this one does not have a texture **/
                if ( !gid )
                    continue;

                /**
                * In the Tiled map format gid indices begin at index 1, index 0
                * is reserved for an empty tile.
                * Since the tileset tile definitions are saved in a vector, their
                * indices begin at 0. When retrieving the tile texture we
                * have to subtract the calculated gid by 1.
                */
                sf::Texture& tex = mTextures.get( mMap.getTiles()->at( gid - 1 ).key );

                /**
                * Create the game object and its components.
                * We do not use createGameObject( ... ) at this point since the game objects
                * belong to their respective grids and are not handled by the world directly.
                */
                sf::Vector2f pos = sf::Vector2f( j * grid->getTileSize(), i * grid->getTileSize() );
                sf::Vector2f size( grid->getTileSize(), grid->getTileSize() );
                GameObject* obj = new GameObject( this, "Static Box", pos, size );
                TextureGraphicsComponent* tgc = new TextureGraphicsComponent( obj );
                tgc->setTexture( &tex, mMap.getTiles()->at( gid - 1 ).rect );
                obj->setGraphicComponent( tgc );


                /** Only add a physics component if the game object is from the layer world **/
                if ( layer.name == "World" )
                {
                    Box2DPhysicsComponent* staticPhysics = new Box2DPhysicsComponent( obj );
                    staticPhysics->createCollisionBody( &mPhysics, obj, b2_staticBody, false );
//                    staticPhysics->setContactable( true );
                    obj->attachComponent( "PhysicsComponent", staticPhysics );
                }

                /** Add the game object to the grid **/
                grid->addTile( grid->getTileKeyByPosition( pos ), obj );
            }
        }

        mGrids.push_back( std::unique_ptr<Grid>( grid ) );
    }


    try
    {
        sf::Vector2f position = sf::Vector2f( mMap.getObjectGroups()->at( "Player" ).objects.at( 0 ).position.left,
                mMap.getObjectGroups()->at( "Player" ).objects.at( 0 ).position.top );
        sf::Vector2f size = sf::Vector2f( 10.f, 11.f );
        mPlayer = this->createGameObject( "Player", position, size );
    }
    catch ( std::out_of_range oor )
    {
        // No player
    }

    this->createEnemies();
}

void World::initializeTextures()
{
    mTextures.load( "ror", "media/textures/ror.png" );
    mTextures.load( "golem", "media/textures/golem/golem.png" );
}

void World::initializeSounds()
{
    mSounds.load( "shoot", "media/sounds/shoot.wav" );
    mSounds.load( "clap", "media/sounds/clap.wav" );
}

GameObject* World::createGameObject( std::string name, sf::Vector2f position, sf::Vector2f size )
{
    GameObject* obj = mGameObjectFactory.createObject( this, name, position, size );

    mObjectsToCreate.push_back( std::unique_ptr<GameObject>( obj ) );

    return obj;
}

void World::createEnemies()
{
    try
    {
        for ( auto obj : mMap.getObjectGroups()->at( "Enemies" ).objects )
        {
            sf::Vector2f position( sf::Vector2f( obj.position.left, obj.position.top ) );
            sf::Vector2f size( 20.f, 30.f );

            GameObject* object = this->createGameObject( obj.name, position, size );
            object->setProperties( obj.properties );
        }

        for ( auto obj : mMap.getObjectGroups()->at( "EnemySpawner" ).objects )
        {
            sf::Vector2f position( sf::Vector2f( obj.position.left, obj.position.top ) );
            sf::Vector2f size( 20.f, 30.f );

            GameObject* object = this->createGameObject( obj.name, position, size );
            SolidColorGraphicsComponent* solid = new SolidColorGraphicsComponent( object );
            solid->setDrawn( false );
            object->setGraphicComponent( solid );

            SpawnerComponent* spawn = new SpawnerComponent( object );

            for ( std::tuple<std::string, std::string> property : obj.properties )
            {
                if ( std::get<0>( property ) == "amountMax" )
                {
                    spawn->setAmountMax( atoi( std::get<1>( property ).c_str() ) );
                }

                if ( std::get<0>( property ) == "intervalMin" )
                {
                    spawn->setIntervalMin( atoi( std::get<1>( property ).c_str() ) );
                }

                if ( std::get<0>( property ) == "intervalMax" )
                {
                    spawn->setIntervalMax( ( atoi( std::get<1>( property ).c_str() ) ) );
                }

                if ( std::get<0>( property ) == "type" )
                {
                    spawn->setGameObjectType( std::get<1>( property ).c_str() );
                }
            }

            object->attachComponent( "SpawnerComponent", spawn );
        }
    }
    catch ( std::out_of_range oor )
    {
        // No enemies
    }
}
