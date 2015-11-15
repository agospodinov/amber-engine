#ifndef RENDERSTAGE_H
#define RENDERSTAGE_H

#include <vector>

#include "Amber/Rendering/IRenderTarget.h"
#include "Amber/Rendering/Reference.h"
#include "Amber/Rendering/ShaderPass.h"

#include "Amber/Rendering/ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class RenderStage
        {
            public:
                RenderStage(Reference<IRenderTarget> renderTarget, bool clearBeforeRendering = true);
                RenderStage(const RenderStage &other) = default;
                RenderStage(RenderStage &&other) noexcept = default;
                ~RenderStage() = default;

                RenderStage &operator =(const RenderStage &other) = default;
                RenderStage &operator =(RenderStage &&other) noexcept = default;

                Reference<IRenderTarget> getRenderTarget() const;

                const std::vector<ShaderPass> &getShaderPasses() const;
                void addShaderPass(ShaderPass shaderPass);

                bool shouldClearBeforeRendering() const;
                void setClearBeforeRendering(bool clearBeforeRendering);

                void setup(IRenderer *renderer);

            private:
                Reference<IRenderTarget> renderTarget;
                std::vector<ShaderPass> shaderPasses;
                bool clearBeforeRendering;
        };
    }
}

#endif // RENDERSTAGE_H