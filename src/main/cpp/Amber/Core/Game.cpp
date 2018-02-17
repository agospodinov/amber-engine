#include "Game.h"

#include "Amber/Core/Scene.h"

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

        Scene &Game::getScene()
        {
            return scene;
        }

        const Scene &Game::getScene() const
        {
            return scene;
        }

        void Game::setScene(Scene scene)
        {
            this->scene = std::move(scene);

            for (Entity &entity : this->scene.entities)
            {
                for (const std::unique_ptr<ISystem> &system : systems)
                {
                    system->registerEntity(entity);
                }
            }
        }
    }
}
