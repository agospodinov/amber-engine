#ifndef GAME_H
#define GAME_H

#include <memory>

#include "Amber/Rendering/IRenderer.h"

#include "Amber/Utilities/Defines.h"

namespace Amber
{
    namespace Core
    {
        class AMBER_EXPORTS Game
        {
            public:
                Game() = default;
                ~Game() = default;

            private:
                std::unique_ptr<Rendering::IRenderer> renderer;
        };
    }
}
#endif // GAME_H
