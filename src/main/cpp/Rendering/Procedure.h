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
                static Procedure getDefaultProcedure(IContext &context);

                Procedure() = default;

                std::deque<Rendering::RenderStage> &getRenderStages();
                const std::deque<Rendering::RenderStage> &getRenderStages() const;
                void prependRenderStage(Rendering::RenderStage renderStage);
                void appendRenderStage(Rendering::RenderStage renderStage);

            private:
                std::deque<RenderStage> renderStages;
        };
    }
}

#endif // PROCEDURE_H
