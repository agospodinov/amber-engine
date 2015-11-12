#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <vector>

#include "Amber/Rendering/RenderStage.h"

namespace Amber
{
    namespace Rendering
    {
        class Procedure
        {
            public:
                Procedure() = default;
                ~Procedure() = default;

                std::vector<RenderStage> &getRenderStages();
                const std::vector<RenderStage> &getRenderStages() const;
                void prependRenderStage(RenderStage renderStage);
                void appendRenderStage(RenderStage renderStage);

            private:
                std::vector<RenderStage> renderStages;
        };
    }
}

#endif // PROCEDURE_H
