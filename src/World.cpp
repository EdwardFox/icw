#include "lib/World.hpp"
#include "lib/components/TestAIComponent.hpp"
#include "lib/components/TestInputComponent.hpp"
#include "lib/components/Box2DPhysicsComponent.hpp"
#include "lib/components/SolidColorGraphicsComponent.hpp"
#include "lib/components/TextureGraphicsComponent.hpp"
#include "lib/components/AnimationGraphicsComponent.hpp"

World::World() :
        mTextures()
        , mGrid()
        , mPhysics( b2Vec2( 0.f, 9.8f ) )
        , test()
{
    // Initialize Resources
    initializeTextures();

    for ( int i = 0; i < 3; ++i )
    {
        for ( int j = 0; j < 20; ++j )
        {
            // Create entity and add to grid
            sf::Vector2f pos;
            if ( j % 2 == 0 )
            {
                pos = sf::Vector2f( j * mGrid.getTileSize(), i * mGrid.getTileSize() + 350 );
            }
            else
            {
                pos = sf::Vector2f( j * mGrid.getTileSize(), i * mGrid.getTileSize() + 300 );
            }
            sf::Vector2f size( mGrid.getTileSize(), mGrid.getTileSize() );

            GameObject* obj = new GameObject();
            SolidColorGraphicsComponent* dgc = new SolidColorGraphicsComponent( size );
            obj->setGraphicComponent( dgc );
            obj->setPosition( pos );
            obj->setSize( size );

            Box2DPhysicsComponent* staticPhysics = new Box2DPhysicsComponent( mPhysics, *obj, b2_kinematicBody );
            obj->attachComponent( "PhysicsComponent", staticPhysics );

            if ( j % 2 == 0 )
            {
                TestAIComponent* tac = new TestAIComponent();
                obj->attachComponent( "TestAIComponent", tac );
            }

            mGrid.addTile( mGrid.getTileKeyByPosition( pos ), obj );
        }
    }

    sf::Vector2f pos( 50.f, 50.f );
    sf::Texture& tex = mTextures.get( "animation" );

    AnimationGraphicsComponent* dgc = new AnimationGraphicsComponent();
    dgc->setTexture( tex );

    Animation anim;
    anim.addFrame( sf::Vector2f( 1.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 33.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 65.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 97.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 129.f, 0.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 1.f, 33.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 33.f, 33.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 65.f, 33.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 97.f, 33.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.addFrame( sf::Vector2f( 129.f, 33.f ), sf::Vector2f( 32.f, 32.f ) );
    anim.setTimePerFrame( 250 );

    dgc->addAnimation( "default", anim );
    dgc->setAnimation( "default" );

    test.setGraphicComponent( dgc );
    test.setPosition( pos );
    test.setSize( sf::Vector2f( 32.f, 32.f ) );

    Box2DPhysicsComponent* dynPhysics = new Box2DPhysicsComponent( mPhysics, test, b2_dynamicBody );
    test.attachComponent( "PhysicsComponent", dynPhysics );

    TestInputComponent* tic = new TestInputComponent();
    test.attachComponent( "TestInputComponent", tic );
}

void World::render( sf::RenderTarget& target, sf::Time dt ) const
{
    mGrid.render( target, dt );
    test.render( target, dt );
}

void World::update( sf::Time dt )
{
    mPhysics.Step( dt.asSeconds(), 8, 3 );

    mGrid.update( dt );
    test.update( dt );
}

void World::initializeTextures()
{
    mTextures.load( "default", "media/textures/DefaultTile.png" );
    mTextures.get( "default" ).setSmooth( true );
    mTextures.load( "animation", "media/textures/DefaultAnimation.png" );
    mTextures.get( "animation" ).setSmooth( true );
}
