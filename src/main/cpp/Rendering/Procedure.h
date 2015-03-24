#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <deque>

#include "RenderStage.h"

namespace Amber
{
    namespace Rendering
    {
        class Procedure
        {
            public:
                Procedure() = default;
                ~Procedure() = default;

                std::deque<RenderStage> &getRenderStages();
                const std::deque<RenderStage> &getRenderStages() const;
                void prependRenderStage(RenderStage renderStage);
                void appendRenderStage(RenderStage renderStage);

            private:
                std::deque<RenderStage> renderStages;
        };
    }
}

#endif // PROCEDURE_H
