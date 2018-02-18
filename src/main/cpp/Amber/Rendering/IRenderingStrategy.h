#ifndef IRENDERINGSTRATEGY_H
#define IRENDERINGSTRATEGY_H

#include "Amber/Rendering/Scene.h"
#include "Amber/Rendering/Backend/IRenderer.h"

namespace Amber
{
    namespace Rendering
    {
        class IRenderingStrategy
        {
            public:
                IRenderingStrategy() = default;
                virtual ~IRenderingStrategy() = default;

                virtual void render(Scene &scene, IRenderer *renderer) = 0;
        };
    }
}

#endif // IRENDERINGSTRATEGY_H
