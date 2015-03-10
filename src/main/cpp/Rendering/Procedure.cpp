#include "Procedure.h"

#include "IO/ShaderLoader.h"

namespace Amber
{
    namespace Rendering
    {
        // FIXME rework
        Procedure Procedure::getDefaultProcedure(IContext &context)
        {
            Procedure defaultProcedure;
            Rendering::RenderStage finalRenderStage(context.getDefaultRenderTarget());
            IO::ShaderLoader shaderLoader;

            {
                Rendering::Reference<Rendering::IShader> vertexShader = context.createShader(Rendering::IShader::Type::VertexShader);
                shaderLoader.loadShader("Skybox", vertexShader);

                Rendering::Reference<Rendering::IShader> pixelShader = context.createShader(Rendering::IShader::Type::PixelShader);
                shaderLoader.loadShader("Skybox", pixelShader);

                Rendering::Reference<Rendering::IProgram> skyboxProgram = context.createProgram();
                skyboxProgram->addShader(vertexShader);
                skyboxProgram->addShader(pixelShader);

                Rendering::ShaderPass environmentPass(std::move(skyboxProgram), Rendering::Node::Type::World);
                finalRenderStage.addShaderPass(std::move(environmentPass));
            }

            {
                Rendering::Reference<Rendering::IShader> vertexShader = context.createShader(Rendering::IShader::Type::VertexShader);
                shaderLoader.loadShader("Model", vertexShader);

                Rendering::Reference<Rendering::IShader> pixelShader = context.createShader(Rendering::IShader::Type::PixelShader);
                shaderLoader.loadShader("Model", pixelShader);

                Rendering::Reference<Rendering::IProgram> modelsProgram = context.createProgram();
                modelsProgram->addShader(vertexShader);
                modelsProgram->addShader(pixelShader);

                Rendering::ShaderPass modelsPass(std::move(modelsProgram), Rendering::Node::Type::Model);
                finalRenderStage.addShaderPass(std::move(modelsPass));
            }

            defaultProcedure.appendRenderStage(std::move(finalRenderStage));

            return defaultProcedure;
        }

        std::deque<RenderStage> &Procedure::getRenderStages()
        {
            return renderStages;
        }

        const std::deque<RenderStage> &Procedure::getRenderStages() const
        {
            return renderStages;
        }

        void Procedure::prependRenderStage(RenderStage renderStage)
        {
            this->renderStages.push_front(std::move(renderStage));
        }

        void Procedure::appendRenderStage(RenderStage renderStage)
        {
            this->renderStages.push_back(std::move(renderStage));
        }
    }
}
