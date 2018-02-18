#include "World.h"

#include <functional>
#include <memory>

namespace Amber
{
    namespace Core
    {
        World::World(std::vector<Entity> entities)
            : entities(std::move(entities))
        {
        }


        World::World(World &&other) noexcept
            : entities(std::move(other.entities))
        {
        }

        World &World::operator =(World &&other) noexcept
        {
            if (this != &other)
            {
                entities = std::move(other.entities);
            }

            return *this;
        }

        std::vector<Entity> &World::getEntities()
        {
            return entities;
        }

        const std::vector<Entity> &World::getEntities() const
        {
            return entities;
        }
    }
}
