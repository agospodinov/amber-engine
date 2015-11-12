#ifndef SCENE_H
#define SCENE_H

#include "Amber/Rendering/IRenderable.h"

#include <vector>

#include "Amber/Rendering/Node.h"
#include "Amber/Rendering/Camera.h"
#include "Amber/Rendering/Skybox.h"

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
