#include "Scene.h"

#include <functional>
#include <memory>

namespace Amber
{
    namespace Core
    {
        Scene::Scene(std::vector<Entity> entities)
            : entities(std::move(entities))
        {
        }


        Scene::Scene(Scene &&other) noexcept
            : entities(std::move(other.entities))
        {
        }

        Scene &Scene::operator =(Scene &&other) noexcept
        {
            if (this != &other)
            {
                entities = std::move(other.entities);
            }

            return *this;
        }

        std::vector<Entity> &Scene::getEntities()
        {
            return entities;
        }

        const std::vector<Entity> &Scene::getEntities() const
        {
            return entities;
        }
    }
}
