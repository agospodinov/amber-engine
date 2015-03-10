#ifndef IRENDERTARGET_H
#define IRENDERTARGET_H

#include "IBindable.h"
#include "Reference.h"

namespace Amber
{
    namespace Rendering
    {
        class ITexture;

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

                virtual void attach(AttachmentType type, Reference<ITexture> texture) = 0;
        };
    }
}

#endif // IRENDERTARGET_H