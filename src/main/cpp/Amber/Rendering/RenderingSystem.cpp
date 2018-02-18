#include "RenderingSystem.h"

#include "Amber/Utilities/Config.h"

#include "Amber/IO/ShaderLoader.h"
#include "Amber/Rendering/IRenderingStrategy.h"
#include "Amber/Rendering/Camera.h"
#include "Amber/Rendering/Backend/OpenGL4/OpenGL4Renderer.h"

namespace Amber
{
    namespace Rendering
    {
        // FIXME add support for loading platform specific renderer
        // and loading custom renderers
        RenderingSystem::RenderingSystem(Core::Game &game)
            : renderer(new GL4::OpenGL4Renderer()),
              game(&game)
        {
        }

        bool RenderingSystem::isOnSeparateThread() const
        {
            return false; // FIXME temporary
        }

        void RenderingSystem::runSingleIteration()
        {
            renderingStrategy->render(scene, renderer.get());
        }

        void RenderingSystem::run()
        {
            // FIXME no-op
        }

        void RenderingSystem::registerEntity(Core::Entity &entity)
        {
            registerProxy<Mesh, Material, Core::Transform>(entity, [=] (auto p) {
                renderer->prepare(*p.template get<Mesh>());
                scene.addMesh(p);
            });
            registerProxy<Light, Core::Transform>(entity, [=] (auto p) { scene.addLight(p); });
        }

        Viewport &RenderingSystem::getViewport()
        {
            return viewport;
        }
    }
}
