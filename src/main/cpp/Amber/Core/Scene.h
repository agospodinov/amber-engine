#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "Amber/Core/Entity.h"

namespace Amber
{
    namespace Core
    {
        class Scene
        {
            public:
                Scene() = default;
                Scene(std::vector<Entity> entities);
                Scene(const Scene &other) = delete;
                Scene(Scene &&other) noexcept;
                ~Scene() = default;

                Scene &operator =(const Scene &other) = delete;
                Scene &operator =(Scene &&other) noexcept;

                std::vector<Entity> &getEntities();
                const std::vector<Entity> &getEntities() const;

            private:
                std::vector<Entity> entities;
        };
    }
}

#endif // SCENE_H
