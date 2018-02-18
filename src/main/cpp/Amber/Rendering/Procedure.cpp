#include "Procedure.h"

namespace Amber
{
    namespace Rendering
    {
        std::vector<RenderStage> &Procedure::getRenderStages()
        {
            return renderStages;
        }

        const std::vector<RenderStage> &Procedure::getRenderStages() const
        {
            return renderStages;
        }

        void Procedure::prependRenderStage(RenderStage renderStage)
        {
            this->renderStages.insert(this->renderStages.begin(), std::move(renderStage));
        }

        void Procedure::appendRenderStage(RenderStage renderStage)
        {
            this->renderStages.push_back(std::move(renderStage));
        }
    }
}
