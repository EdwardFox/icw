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
    // Initialize Resources
    initializeTextures();
    mPhysics.SetContactListener( &mListener );

    this->loadMap( "media/maps/Temple.tmx" );
    this->createPlayer();

    mCamera.setOffset( sf::Vector2f( 0.f, -50.f ) );
    mCamera.setZoom( 3.f );
    mCamera.setFollowTarget( mPlayer );
    sf::IntRect rect( 0, 0, mActiveMap->getMapSize().x * mActiveMap->getTileSize().x, mActiveMap->getMapSize().y * mActiveMap->getTileSize().x );
    mCamera.setBorders( rect );
}

void World::render( sf::RenderTarget& target, sf::Time dt, sf::Vector2u windowSize ) const
{
    mCamera.render( target, dt );

    for ( auto& grid : mGrids )
    {
        grid->render( target, dt, windowSize, &mCamera );
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

    for ( auto& object : mObjects )
    {
        object->update( dt );
    }

    for ( auto& object : mObjectsToCreate )
    {
        mObjects.push_back( std::unique_ptr<GameObject>( std::move( object ) ) );
    }
    mObjectsToCreate.clear();
}

void World::loadMap( std::string path )
{
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

    for ( auto& layer : mActiveMap->getLayers() )
    {
        Grid* grid = new Grid( layer.name );

        if ( layer.name == "World" )
            mWorldGrid = grid;

        grid->setTileSize( mActiveMap->getTileSize().x );

        for ( int i = 0; i < layer.rows; ++i )
        {
            for ( int j = 0; j < layer.columns; ++j )
            {
                int gid = layer.gids.at( i * layer.columns + j );
                if ( !gid )
                    continue;

                // Create entity and add to grid
                sf::Vector2f pos;
                pos = sf::Vector2f( j * grid->getTileSize(), i * grid->getTileSize() );
                sf::Vector2f size( grid->getTileSize(), grid->getTileSize() );

                GameObject* obj = new GameObject( this );
                sf::Texture& tex = mTextures.get( mActiveMap->getTiles().at( gid - 1 ).key );
                TextureGraphicsComponent* tgc = new TextureGraphicsComponent();
                tgc->setTexture( tex, mActiveMap->getTiles().at( gid - 1 ).rect );
                obj->setGraphicComponent( tgc );
                obj->setPosition( pos );
                obj->setSize( size );

                if ( layer.name == "World" )
                {
                    Box2DPhysicsComponent* staticPhysics = new Box2DPhysicsComponent( mPhysics, *obj, b2_staticBody );
                    obj->attachComponent( "PhysicsComponent", staticPhysics );
                }

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
    sf::Vector2f position = sf::Vector2f( mActiveMap->getObjectGroups().at( 0 ).objects.at( 0 ).left, mActiveMap->getObjectGroups().at( 0 ).objects.at( 0 ).top );
    sf::Vector2f size = sf::Vector2f( 10.f, 11.f );
    mPlayer = this->createGameObject( position, size );

    this->createPlayerAnimations();
    this->createPlayerStates();

    Box2DPhysicsComponent* dynPhysics = new Box2DPhysicsComponent( mPhysics, *mPlayer, b2_dynamicBody );
    dynPhysics->setFixedRotation( true );
    dynPhysics->createDefaultSensors( mPhysics, *mPlayer );
    mPlayer->attachComponent( "PhysicsComponent", dynPhysics );

    PlayerInputComponent* tic = new PlayerInputComponent();
    mPlayer->attachComponent( "InputComponent", tic );

    PlayerMovementComponent* pmc = new PlayerMovementComponent();
    mPlayer->attachComponent( "MovementComponent", pmc );

    ActionComponent* ac = new ActionComponent();
    ac->addAction(
            "shoot", [this]( GameObject& object )
        {
            sf::Vector2f velocity( 10.f, 0.f );
            sf::Vector2f size( 4.f, 4.f );
            sf::Vector2f pos = object.getPosition();

            float offsetX = 15.f;

            AnimationGraphicsComponent* animComp = dynamic_cast<AnimationGraphicsComponent*>(object.getGraphicComponent());
            if ( animComp )
            {
                if ( animComp->getFlipped().x == -1.f )
                {
                    offsetX = -offsetX;
                    velocity.x = -velocity.x;
                }
            }

            pos.x += offsetX;

            GameObject* projectile = object.mWorld->createGameObject( pos, size );
            projectile->setPosition( pos );
            projectile->setSize( size );

            SolidColorGraphicsComponent* solid = new SolidColorGraphicsComponent( projectile->getSize() );
            projectile->setGraphicComponent( solid );

            Box2DPhysicsComponent* box = new Box2DPhysicsComponent( mPhysics, *projectile, b2_dynamicBody );
            box->setGravityScale( 0.f );
            box->setContactable( true );
            projectile->attachComponent( "PhysicsComponent", box );

            ProjectileAIComponent* proj = new ProjectileAIComponent();
            proj->setVelocity( velocity );
            projectile->attachComponent( "InputComponent", proj );
        }
    );
    mPlayer->attachComponent( "ActionComponent", ac );
}

void World::createPlayerAnimations()
{
    sf::Texture& tex = mTextures.get( "ror" );
    AnimationGraphicsComponent* agc = new AnimationGraphicsComponent();
    agc->setTexture( tex );

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
    attack.setTimePerFrame( 25 );
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

    DefaultStateHandlerComponent* dsc = new DefaultStateHandlerComponent();
    dsc->addState( "idle", idle );
    dsc->addState( "run", run );
    dsc->addState( "jump", jump );
    dsc->addState( "land", land );
    dsc->addState( "attack", attack );
    dsc->setStartState( "idle" );

    mPlayer->attachComponent( "StateHandlerComponent", dsc );
}

GameObject* World::createGameObject( sf::Vector2f position, sf::Vector2f size )
{
    GameObject* obj = new GameObject( this );
    obj->setPosition( position );
    obj->setSize( size );

    mObjectsToCreate.push_back( std::unique_ptr<GameObject>( obj ) );

    return obj;
}
