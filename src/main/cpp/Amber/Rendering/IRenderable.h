#ifndef IRENDERABLE_H
#define IRENDERABLE_H

#include "Amber/Rendering/ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class IRenderable
        {
            public:
                IRenderable() = default;
                virtual ~IRenderable() = default;

                virtual void setup(IRenderer *renderer) = 0;
                virtual void render(IRenderer *renderer) = 0;
        };
    }
}

#endif // IRENDERABLE_H
