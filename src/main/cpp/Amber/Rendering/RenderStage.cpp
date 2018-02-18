#include "RenderStage.h"

#include <algorithm>
#include <functional>

#include "Amber/Rendering/Backend/IBindable.h"
#include "Amber/Rendering/Backend/IProgram.h"
#include "Amber/Rendering/Backend/IRenderer.h"
#include "Amber/Rendering/Backend/Reference.h"

namespace Amber
{
    namespace Rendering
    {
        RenderStage::RenderStage(Reference<IRenderTarget> renderTarget, bool clearBeforeRendering)
            : renderTarget(renderTarget),
              clearBeforeRendering(clearBeforeRendering)
        {
        }

        Reference<IRenderTarget> RenderStage::getRenderTarget() const
        {
            return renderTarget;
        }

        bool RenderStage::shouldClearBeforeRendering() const
        {
            return clearBeforeRendering;
        }

        void RenderStage::setClearBeforeRendering(bool clearBeforeRendering)
        {
            this->clearBeforeRendering = clearBeforeRendering;
        }

        const std::vector<ShaderPass> &RenderStage::getShaderPasses() const
        {
            return shaderPasses;
        }

        void RenderStage::addShaderPass(ShaderPass shaderPass)
        {
            shaderPasses.push_back(std::move(shaderPass));
        }
    }
}
