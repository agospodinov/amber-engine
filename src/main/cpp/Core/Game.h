#ifndef GAME_H
#define GAME_H

#include <memory>

#include "Rendering/IRenderer.h"

#include "Utilities/Defines.h"

namespace Amber
{
    namespace Core
    {
        class AMBER_EXPORTS Game
        {
            public:
                Game() = default;

            private:
                std::unique_ptr<Rendering::IRenderer> renderer;
        };
    }
}
#endif // GAME_H
