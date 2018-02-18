#ifndef IOBJECT_H
#define IOBJECT_H

#include <Eigen/Core>

#include "Amber/Rendering/Backend/IBuffer.h"
#include "Amber/Rendering/Backend/Layout.h"
#include "Amber/Rendering/Backend/Reference.h"

namespace Amber
{
    namespace Rendering
    {
        class IObject
        {
            public:
                IObject() = default;
                virtual ~IObject() = default;

                virtual Reference<IBuffer> &getVertexBuffer() = 0;
                virtual const Reference<IBuffer> &getVertexBuffer() const = 0;

                virtual Reference<IBuffer> &getIndexBuffer() = 0;
                virtual const Reference<IBuffer> &getIndexBuffer() const = 0;

                virtual Layout &getLayout() = 0;

                virtual bool isInHardwareStorage() const = 0;
                virtual void moveToHardwareStorage(IContext &context) = 0;

                virtual std::size_t getVertexCount() const = 0;
                virtual std::size_t getPrimitiveCount() const = 0;
                virtual std::size_t getInstanceCount() const = 0;
        };
    }
}

#endif // IOBJECT_H
