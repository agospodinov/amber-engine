#include "Scene.h"

#include <functional>
#include <memory>

#include "Node.h"

namespace Amber
{
    namespace Core
    {
        Scene::Scene()
        {
        }

        Scene::Scene(std::unique_ptr<Node> worldNode)
            : worldNode(std::move(worldNode))
        {
        }

        Scene::Scene(Scene &&other) noexcept
            : worldNode(std::move(other.worldNode))
        {
        }

        Scene::~Scene()
        {
        }

        Scene &Scene::operator =(Scene &&other) noexcept
        {
            if (this != &other)
            {
                worldNode = std::move(other.worldNode);
            }

            return *this;
        }

        Node *Scene::getWorldNode()
        {
            return worldNode.get();
        }

        const Node *Scene::getWorldNode() const
        {
            return worldNode.get();
        }
    }
}
