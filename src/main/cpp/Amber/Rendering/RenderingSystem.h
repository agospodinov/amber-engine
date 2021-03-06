#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include "Amber/Core/ISystem.h"

#include <memory>

#include "Amber/Core/Game.h"
#include "Amber/Rendering/Backend/IRenderer.h"
#include "Amber/Rendering/IRenderingStrategy.h"
#include "Amber/Rendering/Scene.h"
#include "Amber/Rendering/Viewport.h"

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

                Viewport &getViewport();

            private:
                Scene scene;
                Viewport viewport;
                std::unique_ptr<IRenderer> renderer;
                std::unique_ptr<IRenderingStrategy> renderingStrategy;
                Core::Game *game;
        };
    }
}

#endif // RENDERINGSYSTEM_H
