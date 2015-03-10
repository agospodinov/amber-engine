#include "RenderStage.h"

#include <algorithm>
#include <functional>

#include "IBindable.h"
#include "IProgram.h"
#include "IRenderer.h"
#include "BindLock.h"
#include "Reference.h"

namespace Amber
{
    namespace Rendering
    {
        RenderStage::RenderStage(Reference<IRenderTarget> renderTarget, bool clearBeforeRendering)
            : renderTarget(renderTarget),
              clearBeforeRendering(clearBeforeRendering)
        {
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

        void RenderStage::setup(IRenderer *renderer)
        {
            renderer->prepare(renderTarget);
            std::for_each(shaderPasses.begin(), shaderPasses.end(), std::bind(&ShaderPass::setup, std::placeholders::_1, renderer));
        }

        void RenderStage::render(IRenderer *renderer)
        {
            BindLock lock(renderTarget.cast<IBindable>());

            if (clearBeforeRendering)
            {
                renderer->clear();
            }
            std::for_each(shaderPasses.begin(), shaderPasses.end(), std::bind(&ShaderPass::render, std::placeholders::_1, renderer));
        }
    }
}
