#include "lib/World.hpp"
#include "lib/components/TestAIComponent.hpp"
#include "lib/components/PlayerInputComponent.hpp"
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/components/TextureGraphicsComponent.hpp"
#include "lib/components/AnimationGraphicsComponent.hpp"
#include "lib/components/PlayerStateHandlerComponent.hpp"
#include "lib/components/PlayerMovementComponent.hpp"

World::World() :
        mTextures()
        , mGrid()
        , mPhysics( b2Vec2( 0.f, 9.8f ) )
        , mPlayer()
{
    // Initialize Resources
    initializeTextures();

    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 20; ++j )
        {
            // Create entity and add to grid
            sf::Vector2f pos;
            pos = sf::Vector2f( j * mGrid.getTileSize(), i * mGrid.getTileSize() + 300 );
            sf::Vector2f size( mGrid.getTileSize(), mGrid.getTileSize() );

            GameObject* obj = new GameObject();
            SolidColorGraphicsComponent* dgc = new SolidColorGraphicsComponent( size );
            obj->setGraphicComponent( dgc );
            obj->setPosition( pos );
            obj->setSize( size );

            Box2DPhysicsComponent* staticPhysics = new Box2DPhysicsComponent( mPhysics, *obj, b2_kinematicBody );
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
}

void World::render( sf::RenderTarget& target, sf::Time dt ) const
{
    mGrid.render( target, dt );
    mPlayer.render( target, dt );
}

void World::update( sf::Time dt )
{
    mPhysics.Step( dt.asSeconds(), 8, 3 );

    mGrid.update( dt );
    mPlayer.update( dt );
}

void World::initializeTextures()
{
    mTextures.load( "default", "media/textures/DefaultTile.png" );
    mTextures.get( "default" ).setSmooth( true );
    mTextures.load( "animation", "media/textures/DefaultAnimation.png" );
    mTextures.get( "animation" ).setSmooth( true );
}

void World::createPlayer()
{
    sf::Vector2f pos( 500.f, 50.f );

    createPlayerAnimations();

    mPlayer.setPosition( pos );
    mPlayer.setSize( sf::Vector2f( 32.f, 32.f ) );

    createPlayerStates();

    Box2DPhysicsComponent* dynPhysics = new Box2DPhysicsComponent( mPhysics, mPlayer, b2_dynamicBody );
    dynPhysics->createGroundSensor( mPhysics, mPlayer, 3 );
    dynPhysics->setFixedRotation( true );
    dynPhysics->setTag( 3 );
    mPlayer.attachComponent( "PhysicsComponent", dynPhysics );

    PlayerInputComponent* tic = new PlayerInputComponent();
    mPlayer.attachComponent( "PlayerInputComponent", tic );

    PlayerMovementComponent* pmc = new PlayerMovementComponent();
    mPlayer.attachComponent( "PlayerMovementComponent", pmc );
}

void World::createPlayerAnimations()
{
    sf::Texture& tex = mTextures.get( "animation" );

    AnimationGraphicsComponent* dgc = new AnimationGraphicsComponent();
    dgc->setTexture( tex );

    Animation idleAnim;
    idleAnim.addFrame( sf::Vector2f( 96.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    idleAnim.setTimePerFrame( 250 );
    dgc->addAnimation( "idle", idleAnim );

    Animation runLeftAnim;
    runLeftAnim.addFrame( sf::Vector2f( 0.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    runLeftAnim.setTimePerFrame( 250 );
    dgc->addAnimation( "runLeft", runLeftAnim );

    Animation runRightAnim;
    runRightAnim.addFrame( sf::Vector2f( 32.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    runRightAnim.setTimePerFrame( 250 );
    dgc->addAnimation( "runRight", runRightAnim );

    Animation jumpAnim;
    jumpAnim.addFrame( sf::Vector2f( 64.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    jumpAnim.setTimePerFrame( 250 );
    dgc->addAnimation( "jump", jumpAnim );

    dgc->setAnimation( "idle" );

    mPlayer.setGraphicComponent( dgc );

}

void World::createPlayerStates()
{
    std::function<std::string( GameObject& object )> idleAction = createStateAction( "idle", "idle" );
    std::function<std::string( GameObject& object )> runLeftAction = createStateAction( "runLeft", "runLeft" );
    std::function<std::string( GameObject& object )> runRightAction = createStateAction( "runRight", "runRight" );
    std::function<std::string( GameObject& object )> jumpAction = createStateAction( "jump", "jump" );
    std::function<std::string( GameObject& object )> fallAction = createStateAction( "fall", "fall" );
    std::function<std::string( GameObject& object )> hitGroundAction = createStateAction( "idle", "hitGround" );
    std::function<std::string( GameObject& object )> fallLeftAction = createStateAction( "fallLeft", "fallLeft" );
    std::function<std::string( GameObject& object )> fallRightAction = createStateAction( "fallRight", "fallRight" );

    State idle( "idle" );
    idle.addAction( "runLeft", runLeftAction );
    idle.addAction( "runRight", runRightAction );
    idle.addAction( "jump", jumpAction );

    State runRight( "runRight" );
    runRight.addAction( "idle", idleAction );
    runRight.addAction( "runLeft", runLeftAction );
    runRight.addAction( "jump", jumpAction );

    State runLeft( "runLeft" );
    runLeft.addAction( "idle", idleAction );
    runLeft.addAction( "runRight", runRightAction );
    runLeft.addAction( "jump", jumpAction );

    State jump( "jump" );
    jump.addAction( "fall", fallAction );

    State fall( "fall" );
    fall.addAction( "hitGround", hitGroundAction );
    fall.addAction( "fallLeft", fallLeftAction );
    fall.addAction( "fallRight", fallRightAction );

    State fallLeft( "fallLeft" );
    fallLeft.addAction( "hitGround", hitGroundAction );
    fallLeft.addAction( "fallRight", fallRightAction );
    fallLeft.addAction( "fall", fallAction );

    State fallRight( "fallRight" );
    fallRight.addAction( "hitGround", hitGroundAction );
    fallRight.addAction( "fallLeft", fallLeftAction );
    fallRight.addAction( "fall", fallAction );

    State hitGround( "hitGround" );
    hitGround.addAction( "idle", idleAction );
    hitGround.addAction( "runLeft", runLeftAction );
    hitGround.addAction( "runRight", runRightAction );

    PlayerStateHandlerComponent* pshc = new PlayerStateHandlerComponent();
    pshc->addState( "idle", idle );
    pshc->addState( "runLeft", runLeft );
    pshc->addState( "runRight", runRight );
    pshc->addState( "jump", jump );
    pshc->addState( "fall", fall );
    pshc->addState( "fallLeft", fallLeft );
    pshc->addState( "fallRight", fallRight );
    pshc->addState( "hitGround", hitGround );
    pshc->setStartState( "idle" );
    mPlayer.attachComponent( "StateHandlerComponent", pshc );
}

std::function<std::string( GameObject& object )> World::createStateAction(std::string animation, std::string action)
{
    return [animation, action]( GameObject& object ) -> std::string
    {
        // Play animation
        IGraphicsComponent* graphics = object.getGraphicComponent();
        if ( AnimationGraphicsComponent* agc = dynamic_cast<AnimationGraphicsComponent*>(graphics) )
        {
            agc->setAnimation( animation );
        }

        // Play sound

        return action;
    };
}
