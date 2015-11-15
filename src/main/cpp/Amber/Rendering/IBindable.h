#ifndef IBINDABLE_H
#define IBINDABLE_H

#include <cstdint>

namespace Amber
{
    namespace Rendering
    {
        class IBindable
        {
            public:
                // TODO most likely incomplete enum
                enum class BindType
                {
                    Buffer,
                    RenderTarget,
                    Program,
                    Texture,
                    VertexArray // FIXME API-specific
                };

                IBindable() = default;
                virtual ~IBindable() = default;

                virtual void bind() = 0;
                virtual void unbind() = 0;

                virtual BindType getBindType() const = 0;
                virtual std::uint32_t getBindSlot() const = 0;
        };
    }
}

#endif // IBINDABLE_H
