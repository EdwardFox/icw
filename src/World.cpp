#include "lib/World.hpp"
#include "lib/components/TestAIComponent.hpp"
#include "lib/components/TestInputComponent.hpp"

World::World() :
mGrid()
{
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 20; ++j) {
            // Create entity and add to grid
            sf::Vector2f pos(j*mGrid.getTileSize(), i*mGrid.getTileSize() + 300);
            sf::Vector2f size(mGrid.getTileSize(), mGrid.getTileSize());

            GameObject* obj = new GameObject();
            DefaultGraphicComponent* dgc = new DefaultGraphicComponent(pos, size);
            obj->setGraphicComponent(dgc);
            obj->setPosition(pos);
            obj->setSize(size);

            if(j%2 == 0) {
                TestInputComponent* tic = new TestInputComponent();
                obj->attachComponent("TestInputComponent", tic);

                TestAIComponent* tac = new TestAIComponent();
                obj->attachComponent("TestAIComponent", tac);
            }

            mGrid.addTile(mGrid.getTileKeyByPosition(pos), obj);
        }
    }
}

void World::render(sf::RenderTarget& target, sf::Time dt) const
{
    mGrid.render(target, dt);
}

void World::update(sf::Time dt)
{
    mGrid.update(dt);
}
