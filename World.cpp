#include "World.hpp"

World::World() :
mGrid()
{
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 20; ++j) {
            // Create entity and add to grid
            sf::Vector2f pos(j*mGrid.getTileSize(), i*mGrid.getTileSize() + 500);
            sf::Vector2f size(mGrid.getTileSize(), mGrid.getTileSize());

            GameObject* obj = new GameObject();
            DefaultGraphicComponent* dgc = new DefaultGraphicComponent(pos, size);
            obj->setGraphicComponent(dgc);
            obj->setPosition(pos);
            obj->setSize(size);
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
