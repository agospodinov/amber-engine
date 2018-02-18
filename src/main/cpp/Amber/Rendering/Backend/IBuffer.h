#ifndef IBUFFER_H
#define IBUFFER_H

#include "Amber/Rendering/Backend/IMultiBindable.h"

#include "Amber/Utilities/ScopedDataPointer.h"

namespace Amber
{
    namespace Rendering
    {
        class IBuffer : public IMultiBindable
        {
            public:
                enum class Type
                {
                    Vertex,
                    Index,
                    Constant
                };

                IBuffer() = default;
                IBuffer(const IBuffer &other) = delete;
                IBuffer(IBuffer &&other) = default;
                virtual ~IBuffer() = default;

                IBuffer &operator =(const IBuffer &other) = delete;
                IBuffer &operator =(IBuffer &&other) noexcept = default;

                virtual Type getType() const = 0;
                virtual void setType(Type type) = 0;

                virtual void assign(std::size_t offset, std::size_t size, const void *data) = 0;

                virtual void migrate(IBuffer &otherStorage) = 0;

                virtual void resize(std::size_t newCapacity) = 0;

                virtual Utilities::ScopedDataPointer data() = 0;

                virtual std::size_t getCapacity() const = 0;
                virtual bool isNull() const = 0;

                virtual void clear() = 0;
        };
    }
}

#endif // IBUFFER_H
