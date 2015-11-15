#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include "Amber/Core/ISystem.h"
#include "Amber/Core/Scene.h"
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

                const std::vector<std::unique_ptr<ISystem>> &getSystems() const;
                void addSystem(std::unique_ptr<ISystem> system);

                Scene &getScene();
                const Scene &getScene() const;
                void setScene(Scene scene);

            private:
                std::vector<std::unique_ptr<ISystem>> systems;
                Scene scene;
        };
    }
}

#endif // GAME_H
