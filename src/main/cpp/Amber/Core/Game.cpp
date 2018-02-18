#include "Game.h"

namespace Amber
{
    namespace Core
    {
        const std::vector<std::unique_ptr<ISystem>> &Game::getSystems() const
        {
            return systems;
        }

        void Game::addSystem(std::unique_ptr<ISystem> system)
        {
            this->systems.push_back(std::move(system));
        }

        World &Game::getWorld()
        {
            return world;
        }

        const World &Game::getWorld() const
        {
            return world;
        }

        void Game::setWorld(World scene)
        {
            this->world = std::move(scene);

            for (Entity &entity : this->world.entities)
            {
                for (const std::unique_ptr<ISystem> &system : systems)
                {
                    system->registerEntity(entity);
                }
            }
        }
    }
}
