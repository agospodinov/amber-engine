#include "RenderingSystem.h"

#include "Amber/Utilities/Config.h"

#include "Amber/IO/ShaderLoader.h"
#include "Amber/Rendering/Camera.h"
#include "Amber/Rendering/OpenGL4/OpenGL4Renderer.h"

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
            renderer->setProcedure(getDefaultProcedure());
        }

        bool RenderingSystem::isOnSeparateThread() const
        {
            return false; // FIXME temporary
        }

        void RenderingSystem::runSingleIteration()
        {
            renderer->render(game->getScene());
        }

        void RenderingSystem::run()
        {
            // FIXME no-op
        }

        void RenderingSystem::registerEntity(Core::Entity &entity)
        {
            registerProxy<Mesh, Material, Core::Transform>(entity, [=] (auto p) {
                renderer->prepare(*p.template get<Mesh>());
                meshes.push_back(p);
            });
            registerProxy<Light, Core::Transform>(entity, [=] (auto p) { lights.push_back(p); });
        }

        void RenderingSystem::handleWindowResize(int width, int height)
        {
            renderer->getViewport().resize(width, height);
        }

        Procedure RenderingSystem::getDefaultProcedure()
        {
            Procedure defaultProcedure;
//            IContext &context = renderer->getContext();
//            IO::ShaderLoader shaderLoader;

//            {
//                Rendering::RenderStage finalRenderStage(renderer->getContext().getDefaultRenderTarget());
//                Rendering::Reference<Rendering::IShader> skyboxVertexShader = context.createShader(Rendering::IShader::Type::VertexShader);
//                Rendering::Reference<Rendering::IShader> skyboxPixelShader = context.createShader(Rendering::IShader::Type::PixelShader);
//                Rendering::Reference<Rendering::IProgram> skyboxProgram = context.createProgram();
//                shaderLoader.loadShader("Skybox", skyboxVertexShader);
//                shaderLoader.loadShader("Skybox", skyboxPixelShader);
//                skyboxProgram->addShader(skyboxVertexShader);
//                skyboxProgram->addShader(skyboxPixelShader);

//                Rendering::ShaderPass environmentPass(std::move(skyboxProgram), Core::IComponent::Type::World);
//                finalRenderStage.addShaderPass(std::move(environmentPass));

//                Rendering::Reference<Rendering::IShader> modelVertexShader = context.createShader(Rendering::IShader::Type::VertexShader);
//                Rendering::Reference<Rendering::IShader> modelPixelShader = context.createShader(Rendering::IShader::Type::PixelShader);
//                Rendering::Reference<Rendering::IProgram> modelProgram = context.createProgram();
//                shaderLoader.loadShader("BaseModel", modelVertexShader);
//                shaderLoader.loadShader("BaseModel", modelPixelShader);
//                modelProgram->addShader(modelVertexShader);
//                modelProgram->addShader(modelPixelShader);

//                Rendering::ShaderPass modelPass(std::move(modelProgram), Core::IComponent::Type::Model);
//                finalRenderStage.addShaderPass(std::move(modelPass));

//                defaultProcedure.appendRenderStage(std::move(finalRenderStage));
//            }

            return defaultProcedure;
        }
    }
}
