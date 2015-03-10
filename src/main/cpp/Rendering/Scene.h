#ifndef SCENE_H
#define SCENE_H

#include "IRenderable.h"

#include <vector>

#include "Node.h"
#include "Camera.h"
#include "Skybox.h"

namespace Amber
{
    namespace Rendering
    {
        class Scene
        {
            public:
                Scene();
                virtual ~Scene() = default;

                Camera &getCamera();
                const Camera &getCamera() const;

                Node &getWorldNode();
                const Node &getWorldNode() const;

            private:
                Node worldNode;
                Camera camera;
        };
    }
}

#endif // SCENE_H
