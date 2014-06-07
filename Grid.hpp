#ifndef GRID_HPP
#define GRID_HPP

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include "Data.hpp"
#include "GameObject.hpp"

class Grid
{
    public:
        typedef std::unique_ptr<GameObject> entPtr;

        Grid();

        GameObject* const getTile(std::string key) const;
        sf::Vector2i getGridPosition(sf::Vector2f position);
        std::string getTileKeyByPosition(sf::Vector2f position);
        unsigned getTileSize() const;
        void addTile(std::string key, GameObject* ent);
        void removeTile(std::string key);
        void setTileSize(unsigned tileSize);
        void render(sf::RenderTarget& target, sf::Time dt) const;
        void update(sf::Time dt);

    private:

        std::map<std::string, entPtr> mGrid;
        unsigned mTileSize;
};

#endif
