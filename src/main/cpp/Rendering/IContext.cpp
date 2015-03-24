#include "IContext.h"

namespace Amber
{
    namespace Rendering
    {
        // FIXME change to unique_ptr
        IContext *IContext::activeContext = nullptr;

        IContext *IContext::getActiveContext()
        {
            return activeContext;
        }
    }
}
