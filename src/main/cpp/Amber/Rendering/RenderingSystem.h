#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include "Amber/Core/ISystem.h"

#include <memory>

#include "Amber/Core/Game.h"
#include "Amber/Core/Transform.h"
#include "Amber/Rendering/IRenderer.h"
#include "Amber/Rendering/Mesh.h"
#include "Amber/Rendering/Material.h"
#include "Amber/Rendering/Light.h"

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

                std::vector<Core::Entity::Proxy<Mesh, Material, Core::Transform>> meshes;
                std::vector<Core::Entity::Proxy<Light, Core::Transform>> lights;
        };
    }
}

#endif // RENDERINGSYSTEM_H
