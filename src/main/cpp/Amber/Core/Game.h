#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "Amber/Core/ISystem.h"
#include "Amber/Core/World.h"
#include "Amber/Utilities/Defines.h"

namespace Amber
{
    namespace Core
    {
        class AMBER_EXPORTS Game
        {
            public:
                Game() = default;
                ~Game() = default;

                const std::vector<std::unique_ptr<ISystem>> &getSystems() const;
                void addSystem(std::unique_ptr<ISystem> system);

                World &getWorld();
                const World &getWorld() const;
                void setWorld(World world);

            private:
                std::vector<std::unique_ptr<ISystem>> systems;
                World world;
        };
    }
}

#endif // GAME_H
