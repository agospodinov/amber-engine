#ifndef RENDERSTAGE_H
#define RENDERSTAGE_H

#include <vector>

#include "Amber/Rendering/Backend/IRenderTarget.h"
#include "Amber/Rendering/Backend/Reference.h"
#include "Amber/Rendering/ShaderPass.h"

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

            private:
                Reference<IRenderTarget> renderTarget;
                std::vector<ShaderPass> shaderPasses;
                bool clearBeforeRendering;
        };
    }
}

#endif // RENDERSTAGE_H
