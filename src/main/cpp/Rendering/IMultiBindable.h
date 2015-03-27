#ifndef IMULTIBINDABLE_H
#define IMULTIBINDABLE_H

#include "IBindable.h"

#include <cstdint>

namespace Amber
{
    namespace Rendering
    {
        class IMultiBindable : public IBindable
        {
            public:
                IMultiBindable() = default;
                virtual ~IMultiBindable() = default;

                virtual void setBindSlot(std::uint32_t bindSlot) = 0;
        };
    }
}

#endif // IMULTIBINDABLE_H
