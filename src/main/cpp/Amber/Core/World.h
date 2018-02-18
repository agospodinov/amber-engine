#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "Amber/Core/Entity.h"

namespace Amber
{
    namespace Core
    {
        class World
        {
            public:
                World() = default;
                World(std::vector<Entity> entities);
                World(const World &other) = delete;
                World(World &&other) noexcept;
                ~World() = default;

                World &operator =(const World &other) = delete;
                World &operator =(World &&other) noexcept;

                std::vector<Entity> &getEntities();
                const std::vector<Entity> &getEntities() const;

            private:
                friend class Game;

                std::vector<Entity> entities;
        };
    }
}

#endif // WORLD_H
