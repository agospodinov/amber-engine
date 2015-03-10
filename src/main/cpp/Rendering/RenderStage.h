#ifndef RENDERSTAGE_H
#define RENDERSTAGE_H

#include <vector>

#include "IRenderTarget.h"
#include "ShaderPass.h"

#include "ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class RenderStage
        {
            public:
                RenderStage(Reference<IRenderTarget> renderTarget, bool clearBeforeRendering = true);
                RenderStage(const RenderStage &other) = delete;
                RenderStage(RenderStage &&other) noexcept = default;
                ~RenderStage() = default;

                RenderStage &operator =(const RenderStage &other) = delete;
                RenderStage &operator =(RenderStage &&other) noexcept = default;

                bool shouldClearBeforeRendering() const;
                void setClearBeforeRendering(bool clearBeforeRendering);

                const std::vector<ShaderPass> &getShaderPasses() const;
                void addShaderPass(ShaderPass shaderPass);

                void setup(IRenderer *renderer);
                void render(IRenderer *renderer);

            private:
                Reference<IRenderTarget> renderTarget;
                std::vector<ShaderPass> shaderPasses;
                bool clearBeforeRendering;
        };
    }
}

#endif // RENDERSTAGE_H