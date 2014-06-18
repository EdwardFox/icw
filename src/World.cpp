#include "lib/World.hpp"
#include "lib/components/TestAIComponent.hpp"
#include "lib/components/TestInputComponent.hpp"
#include "lib/components/DefaultPhysicsComponent.hpp"

World::World() :
mGrid()
, mPhysics(b2Vec2(0.f, 10.f))
, test()
{
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 20; ++j) {
            // Create entity and add to grid
            sf::Vector2f pos;
            if(j%2 == 0) {
                pos = sf::Vector2f(j*mGrid.getTileSize(), i*mGrid.getTileSize() + 350);
            } else {
                pos = sf::Vector2f(j*mGrid.getTileSize(), i*mGrid.getTileSize() + 300);
            }
            sf::Vector2f size(mGrid.getTileSize(), mGrid.getTileSize());

            GameObject* obj = new GameObject();
            DefaultGraphicComponent* dgc = new DefaultGraphicComponent(pos, size);
            obj->setGraphicComponent(dgc);
            obj->setPosition(pos);
            obj->setSize(size);

            DefaultPhysicsComponent* staticPhysics = new DefaultPhysicsComponent(mPhysics, *obj, b2_kinematicBody);
            obj->attachComponent("PhysicsComponent", staticPhysics);

            if(j%2 == 0) {
                TestInputComponent* tic = new TestInputComponent();
                obj->attachComponent("TestInputComponent", tic);

                TestAIComponent* tac = new TestAIComponent();
                obj->attachComponent("TestAIComponent", tac);
            }

            mGrid.addTile(mGrid.getTileKeyByPosition(pos), obj);
        }
    }

    sf::Vector2f size(32.f, 32.f);
    sf::Vector2f pos(50.f, 50.f);
    DefaultGraphicComponent* dgc = new DefaultGraphicComponent(pos, size);
    test.setGraphicComponent(dgc);
    test.setPosition(pos);
    test.setSize(size);

    DefaultPhysicsComponent* dynPhysics = new DefaultPhysicsComponent(mPhysics, test, b2_dynamicBody);
    test.attachComponent("PhysicsComponent", dynPhysics);
}

void World::render(sf::RenderTarget& target, sf::Time dt) const
{
    mGrid.render(target, dt);
    test.render(target, dt);
}

void World::update(sf::Time dt)
{
    mPhysics.Step(dt.asSeconds(), 6, 2);

    mGrid.update(dt);
    test.update(dt);
}
