#include "lib/World.hpp"
#include "lib/components/TestAIComponent.hpp"
#include "lib/components/PlayerInputComponent.hpp"
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/components/TextureGraphicsComponent.hpp"
#include "lib/components/AnimationGraphicsComponent.hpp"
#include "lib/components/PlayerMovementComponent.hpp"
#include "lib/components/DefaultStateHandlerComponent.hpp"

World::World() :
        mTextures()
        , mGrid()
        , mPhysics( b2Vec2( 0.f, 9.8f ) )
        , mCamera()
        , mPlayer()
        , mListener()
        , mListenerTags( 1 )
{
    // Initialize Resources
    initializeTextures();

    mPhysics.SetContactListener( &mListener );

    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 20; ++j )
        {
            if ( i != 2 && j != 2 )
                continue;

            // Create entity and add to grid
            sf::Vector2f pos;
            pos = sf::Vector2f( j * mGrid.getTileSize(), i * mGrid.getTileSize() + 300 );
            sf::Vector2f size( mGrid.getTileSize(), mGrid.getTileSize() );

            GameObject* obj = new GameObject();
            SolidColorGraphicsComponent* dgc = new SolidColorGraphicsComponent( size );
            obj->setGraphicComponent( dgc );
            obj->setPosition( pos );
            obj->setSize( size );

            Box2DPhysicsComponent* staticPhysics = new Box2DPhysicsComponent( mPhysics, *obj, b2_kinematicBody, mListenerTags );
            obj->attachComponent( "PhysicsComponent", staticPhysics );

//            if ( j % 2 == 0 )
//            {
//                TestAIComponent* tac = new TestAIComponent();
//                obj->attachComponent( "TestAIComponent", tac );
//            }

            mGrid.addTile( mGrid.getTileKeyByPosition( pos ), obj );
        }
    }

    createPlayer();

    mCamera.setOffset( sf::Vector2f( 0.f, 0.f ) );
    mCamera.setZoom( 4.f );
    mCamera.setFollowTarget( &mPlayer );
}

void World::render( sf::RenderTarget& target, sf::Time dt ) const
{
    mCamera.render( target, dt );
    mGrid.render( target, dt );
    mPlayer.render( target, dt );
}

void World::update( sf::Time dt )
{
    mPhysics.Step( dt.asSeconds(), 8, 3 );

    mCamera.update( dt );
    mGrid.update( dt );
    mPlayer.update( dt );
}

void World::initializeTextures()
{
    mTextures.load( "default", "media/textures/DefaultTile.png" );
    mTextures.get( "default" ).setSmooth( true );
    mTextures.load( "animation", "media/textures/DefaultAnimation.png" );
    mTextures.get( "animation" ).setSmooth( true );
    mTextures.load( "ror", "media/textures/ror.png" );
}

void World::createPlayer()
{
    sf::Vector2f pos( 50.f, 200.f );

    createPlayerAnimations();

    createPlayerStates();

    mPlayer.setPosition( pos );
    mPlayer.setSize( sf::Vector2f( 10.f, 11.f ) );

    Box2DPhysicsComponent* dynPhysics = new Box2DPhysicsComponent( mPhysics, mPlayer, b2_dynamicBody, mListenerTags );
    dynPhysics->setListener( &mListener );
    dynPhysics->setFixedRotation( true );
    mPlayer.attachComponent( "PhysicsComponent", dynPhysics );

    PlayerInputComponent* tic = new PlayerInputComponent();
    mPlayer.attachComponent( "InputComponent", tic );

    PlayerMovementComponent* pmc = new PlayerMovementComponent();
    mPlayer.attachComponent( "MovementComponent", pmc );
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

    mPlayer.setGraphicComponent( agc );
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

    mPlayer.attachComponent( "StateHandlerComponent", dsc );
}