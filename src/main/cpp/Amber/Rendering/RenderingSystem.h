#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include "Amber/Core/ISystem.h"

#include <memory>

#include "Amber/Core/Game.h"
#include "Amber/Rendering/IRenderer.h"

namespace Amber
{
    namespace Rendering
    {
        class RenderingSystem : public Core::ISystem
        {
            public:
                RenderingSystem(Core::Game &game);
                virtual ~RenderingSystem() = default;

                virtual bool isOnSeparateThread() const;

                virtual void runSingleIteration();
                virtual void run();

                virtual void registerEntity(Core::Entity &entity) override;

                void handleWindowResize(int width, int height);

            private:
                Procedure getDefaultProcedure();

                std::unique_ptr<IRenderer> renderer;
                Core::Game *game;
        };
    }
}

#endif // RENDERINGSYSTEM_H
