#ifndef IRENDERTARGET_H
#define IRENDERTARGET_H

#include "Amber/Rendering/Backend/IBindable.h"
#include "Amber/Rendering/Backend/Reference.h"
#include "Amber/Rendering/ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class IRenderTarget : public IBindable
        {
            public:
                enum class AttachmentType
                {
                    Color,
                    Depth,
                    Stencil,
                    DepthStencil
                };

                IRenderTarget() = default;
                virtual ~IRenderTarget() = default;

                virtual void attach(Reference<ITexture> texture, AttachmentType type, std::uint32_t index) = 0;
        };
    }
}

#endif // IRENDERTARGET_H
