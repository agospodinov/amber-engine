#include "Scene.h"

#include <functional>
#include <memory>

#include "IRenderer.h"
#include "Model.h"

namespace Amber
{
    namespace Rendering
    {
        Scene::Scene()
            : worldNode(std::unique_ptr<IRenderable>(new Skybox()))
        {
        }

        Camera &Scene::getCamera()
        {
            return camera;
        }

        const Camera &Scene::getCamera() const
        {
            return camera;
        }

        Node &Scene::getWorldNode()
        {
            return worldNode;
        }

        const Node &Scene::getWorldNode() const
        {
            return worldNode;
        }
    }
}
