#ifndef IRENDERER_H
#define IRENDERER_H

#include "Utilities/Defines.h"

namespace Amber
{
    namespace Rendering
    {
        class AMBER_EXPORTS IRenderer
        {
            public:
                IRenderer() = default;
                virtual ~IRenderer() = default;
        };
    }
}
#endif // IRENDERER_H
