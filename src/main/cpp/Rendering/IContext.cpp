#include "IContext.h"

namespace Amber
{
    namespace Rendering
    {
        IContext *IContext::activeContext = nullptr;

        IContext *IContext::getActiveContext()
        {
            return activeContext;
        }
    }
}
