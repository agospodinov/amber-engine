#include "Entity.h"

#include "Amber/Core/IComponent.h"

namespace Amber
{
    namespace Core
    {
        Entity::Entity(Entity &&other) noexcept
            : components(std::move(other.components))
        {
        }

        Entity &Entity::operator =(Entity &&other) noexcept
        {
            if (this != &other)
            {
                components = std::move(other.components);
            }

            return *this;
        }
    }
}
