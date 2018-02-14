#include "Scene.h"

#include <functional>
#include <memory>

namespace Amber
{
    namespace Core
    {
        Scene::Scene()
        {
        }


        Scene::Scene(Scene &&other) noexcept
        {
        }

        Scene::~Scene()
        {
        }

        Scene &Scene::operator =(Scene &&other) noexcept
        {
            if (this != &other)
            {
            }

            return *this;
        }
    }
}
