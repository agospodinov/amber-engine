#ifndef ICONTEXT_H
#define ICONTEXT_H

#include <memory>

#include "IBuffer.h"
#include "IShader.h"
#include "ITexture.h"

namespace Amber
{
    namespace Rendering
    {
        class IBindable;
        class IProgram;
        class IRenderTarget;
        template <typename ValueType> class Reference;

        class IContext
        {
            public:
                static IContext *getActiveContext();

                IContext() = default;
                virtual ~IContext() = default;

                virtual void activate() = 0;
                virtual void deactivate() = 0;

                virtual bool isActive() const = 0;

                virtual bool isMultithreadingSupported() const = 0;

                virtual bool tryLock(const Reference<IBindable> &bindable) = 0;
                virtual void lock(const Reference<IBindable> &bindable) = 0;
                virtual void unlock(const Reference<IBindable> &bindable) = 0;

                virtual Reference<IBuffer> createHardwareBuffer(IBuffer::Type type) = 0;
                virtual Reference<IRenderTarget> createRenderTarget() = 0;
                virtual Reference<IShader> createShader(IShader::Type type) = 0;
                virtual Reference<IProgram> createProgram() = 0;
                virtual Reference<ITexture> createTexture(ITexture::Type type) = 0;

                virtual Reference<IRenderTarget> getDefaultRenderTarget() = 0;

            protected:
                static IContext *activeContext;
        };
    }
}

#endif // ICONTEXT_H
