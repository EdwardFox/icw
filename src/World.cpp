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

World::World() :
        mTextures()
        , mGrids()
        , mMaps()
        , mObjects()
        , mObjectsToCreate()
        , mPhysics( b2Vec2( 0.f, 9.8f ) )
        , mCamera()
        , mPlayer( nullptr )
        , mActiveMap( nullptr )
        , mWorldGrid( nullptr )
        , mListener()
{
    /** Initialize textures (as long as the objects do not do it for themselves **/
    initializeTextures();

    /** We need to set out custom contact listener **/
    mPhysics.SetContactListener( &mListener );

    /**
    * Load a test map and create the player.
    * TODO: Create proper user interface to allow choosing different maps
    */
    this->loadMap( "media/maps/Temple.tmx" );
    this->createPlayer();

    /**
    * Set up the camera
    * TODO: Move literals into proper variables
    */
    mCamera.setOffset( sf::Vector2f( 0.f, -50.f ) );
    mCamera.setZoom( 3.f );
    mCamera.setFollowTarget( mPlayer );
    sf::IntRect rect( 0, 0, mActiveMap->getMapSize().x * mActiveMap->getTileSize().x, mActiveMap->getMapSize().y * mActiveMap->getTileSize().x );
    mCamera.setBorders( rect );

    /** Creates a few physical boxes for testing purposes **/
    for ( int i = 0; i < 6; ++i )
    {
        GameObject* box = this->createGameObject( "Dynamic Box", sf::Vector2f( 600.f, 0.f ), sf::Vector2f( 16.f, 16.f ) );
        SolidColorGraphicsComponent* solid = new SolidColorGraphicsComponent( box, box->getSize() );
        box->setGraphicComponent( solid );

        Box2DPhysicsComponent* physBox = new Box2DPhysicsComponent( &mPhysics, box, b2_dynamicBody );
        physBox->setContactable( true );
        box->attachComponent( "PhysicsComponent", physBox );
    }
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
        }
    }
}

void World::update( sf::Time dt, sf::Vector2u windowSize )
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
            IPhysicsComponent* boxComp = dynamic_cast<IPhysicsComponent*>(obj->getComponent( "PhysicsComponent" ));
            boxComp->destroyBody();
            i = mObjects.erase( i );
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
    /**
    * Only load the map when it has not already been loaded.
    * Make sure to clear old grids before creating new ones.
    */
    try
    {
        mActiveMap = &mMaps.at( path );
    }
    catch ( std::out_of_range oor )
    {
        Map map;
        map.load( path, mTextures );
        mMaps.emplace( path, map );
        mActiveMap = &mMaps.at( path );
    }
    mGrids.clear();

    /** Create a grid for each layer **/
    for ( auto& layer : mActiveMap->getLayers() )
    {
        Grid* grid = new Grid( layer.name );

        /** Keep track of the world layer **/
        if ( layer.name == "World" )
            mWorldGrid = grid;

        /** Set tile size **/
        grid->setTileSize( mActiveMap->getTileSize().x );

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
                sf::Texture& tex = mTextures.get( mActiveMap->getTiles().at( gid - 1 ).key );

                /**
                * Create the game object and its components.
                * We do not use createGameObject( ... ) at this point since the game objects
                * belong to their respective grids and are not handled by the world directly.
                */
                GameObject* obj = new GameObject( this, "Static Box" );
                TextureGraphicsComponent* tgc = new TextureGraphicsComponent( obj );
                tgc->setTexture( &tex, mActiveMap->getTiles().at( gid - 1 ).rect );
                obj->setGraphicComponent( tgc );

                sf::Vector2f pos = sf::Vector2f( j * grid->getTileSize(), i * grid->getTileSize() );
                sf::Vector2f size( grid->getTileSize(), grid->getTileSize() );
                obj->setPosition( pos );
                obj->setSize( size );

                /** Only add a physics component if the game object is from the layer world **/
                if ( layer.name == "World" )
                {
                    Box2DPhysicsComponent* staticPhysics = new Box2DPhysicsComponent( &mPhysics, obj, b2_staticBody );
//                    staticPhysics->setContactable( true );
                    obj->attachComponent( "PhysicsComponent", staticPhysics );
                }

                /** Add the game object to the grid **/
                grid->addTile( grid->getTileKeyByPosition( pos ), obj );
            }
        }

        mGrids.push_back( std::unique_ptr<Grid>( grid ) );
    }
}

void World::initializeTextures()
{
    mTextures.load( "ror", "media/textures/ror.png" );
}

void World::createPlayer()
{
    /** Create the player game object **/
    sf::Vector2f position = sf::Vector2f( mActiveMap->getObjectGroups().at( 0 ).objects.at( 0 ).left, mActiveMap->getObjectGroups().at( 0 ).objects.at( 0 ).top );
    sf::Vector2f size = sf::Vector2f( 10.f, 11.f );
    mPlayer = this->createGameObject( "Player", position, size );

    /** Create its animations and states **/
    this->createPlayerAnimations();
    this->createPlayerStates();

    /** Add a physics component with fixed rotations and default sensors **/
    Box2DPhysicsComponent* dynPhysics = new Box2DPhysicsComponent( &mPhysics, mPlayer, b2_dynamicBody );
    dynPhysics->setFixedRotation( true );
    dynPhysics->createDefaultSensors( &mPhysics, mPlayer );
    dynPhysics->setContactable( true );
    mPlayer->attachComponent( "PhysicsComponent", dynPhysics );

    PlayerInputComponent* tic = new PlayerInputComponent( mPlayer );
    mPlayer->attachComponent( "InputComponent", tic );

    PlayerMovementComponent* pmc = new PlayerMovementComponent( mPlayer );
    mPlayer->attachComponent( "MovementComponent", pmc );

    /** Test for action components which can define their own actions **/
    ActionComponent* ac = new ActionComponent( mPlayer );
    ac->addAction(
            "shoot", []( GameObject* object )
    {
        sf::Vector2f velocity( 10.f, 0.f );
        sf::Vector2f size( 4.f, 4.f );
        sf::Vector2f pos = object->getPosition();

        float offsetX = 15.f;

        /**
        * Figure out in which direction the player is looking
        * and modify values accordingly
        * TODO: Find a better place for this information than the animation component
        */
        AnimationGraphicsComponent* animComp = dynamic_cast<AnimationGraphicsComponent*>(object->getGraphicComponent());
        if ( animComp )
        {
            if ( animComp->getFlipped().x == -1.f )
            {
                offsetX = -offsetX;
                velocity.x = -velocity.x;
            }
        }

        pos.x += offsetX;

        /** Create a bunch of projectiles that fly in different directions **/
        for ( float i = 3.f; i > -4.f; --i )
        {
            sf::Vector2f pos2 = pos;
            pos2.y += i * 5;
            velocity.y = i;

            GameObject* projectile = object->getWorld()->createGameObject( "Projectile", pos2, size );

            SolidColorGraphicsComponent* solid = new SolidColorGraphicsComponent( projectile, projectile->getSize() );
            projectile->setGraphicComponent( solid );

        Box2DPhysicsComponent* box = new Box2DPhysicsComponent( object->getWorld()->getPhysicsWorld(), projectile, b2_dynamicBody );
            box->setGravityScale( 0.f );
            box->setContactable( true );
            projectile->attachComponent( "PhysicsComponent", box );

            ProjectileAIComponent* proj = new ProjectileAIComponent( projectile );
            proj->setVelocity( velocity );
            projectile->attachComponent( "InputComponent", proj );
        }
    }
    );
    mPlayer->attachComponent( "ActionComponent", ac );
}

void World::createPlayerAnimations()
{
    sf::Texture& tex = mTextures.get( "ror" );
    AnimationGraphicsComponent* agc = new AnimationGraphicsComponent( mPlayer );
    agc->setTexture( &tex );

    Animation idle( "idle" );
    idle.addFrame( sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 6.f, 11.f ) );
    idle.setTimePerFrame( 100000 );
    agc->addAnimation( "idle", idle );

    Animation run( "run" );
    run.addFrame( sf::Vector2f( 0.f, 22.f ), sf::Vector2f( 7.f, 11.f ) );
    run.addFrame( sf::Vector2f( 10.f, 22.f ), sf::Vector2f( 5.f, 11.f ) );
    run.addFrame( sf::Vector2f( 19.f, 22.f ), sf::Vector2f( 4.f, 11.f ) );
    run.addFrame( sf::Vector2f( 27.f, 22.f ), sf::Vector2f( 6.f, 11.f ) );
    run.addFrame( sf::Vector2f( 35.f, 22.f ), sf::Vector2f( 8.f, 11.f ) );
    run.addFrame( sf::Vector2f( 45.f, 22.f ), sf::Vector2f( 6.f, 11.f ) );
    run.addFrame( sf::Vector2f( 55.f, 22.f ), sf::Vector2f( 5.f, 11.f ) );
    run.addFrame( sf::Vector2f( 64.f, 22.f ), sf::Vector2f( 5.f, 11.f ) );
    run.setTimePerFrame( 50 );
    agc->addAnimation( "run", run );

    Animation jump( "jump" );
    jump.addFrame( sf::Vector2f( 0.f, 11.f ), sf::Vector2f( 9.f, 11.f ) );
    jump.setTimePerFrame( 10000 );
    agc->addAnimation( "jump", jump );

    Animation attack( "attack" );
    attack.addFrame( sf::Vector2f( 0.f, 33.f ), sf::Vector2f( 56.f, 11.f ) );
    attack.addFrame( sf::Vector2f( 65.f, 33.f ), sf::Vector2f( 61.f, 11.f ) );
    attack.addFrame( sf::Vector2f( 129.f, 33.f ), sf::Vector2f( 62.f, 11.f ) );
    attack.addFrame( sf::Vector2f( 194.f, 33.f ), sf::Vector2f( 57.f, 11.f ) );
    attack.addFrame( sf::Vector2f( 258.f, 33.f ), sf::Vector2f( 14.f, 11.f ) );
    attack.setRepeat( false );
    attack.setTimePerFrame( 5 );
    agc->addAnimation( "attack", attack );
    agc->setAnimation( "idle" );

    mPlayer->setGraphicComponent( agc );
}

void World::createPlayerStates()
{
    State idle;
    idle.setName( "idle" );
    idle.setAnimation( "idle" );
    idle.addState( "run" );
    idle.addState( "jump" );
    idle.addState( "attack" );

    State run;
    run.setName( "run" );
    run.setAnimation( "run" );
    run.addState( "idle" );
    run.addState( "jump" );
    run.addState( "attack" );

    State jump;
    jump.setName( "jump" );
    jump.setAnimation( "jump" );
    jump.addState( "land" );
    jump.addState( "attack" );

    State land;
    land.setName( "land" );
    land.setAnimation( "idle" );
    land.addState( "idle" );
    land.addState( "run" );
    land.addState( "attack" );

    State attack;
    attack.setName( "attack" );
    attack.setAnimation( "attack" );
    attack.setReturnToPreviousState( true );

    DefaultStateHandlerComponent* dsc = new DefaultStateHandlerComponent( mPlayer );
    dsc->addState( "idle", idle );
    dsc->addState( "run", run );
    dsc->addState( "jump", jump );
    dsc->addState( "land", land );
    dsc->addState( "attack", attack );
    dsc->setStartState( "idle" );

    mPlayer->attachComponent( "StateHandlerComponent", dsc );
}

GameObject* World::createGameObject( std::string name, sf::Vector2f position, sf::Vector2f size )
{
    GameObject* obj = new GameObject( this, name );
    obj->setPosition( position );
    obj->setSize( size );

    mObjectsToCreate.push_back( std::unique_ptr<GameObject>( obj ) );

    return obj;
}
