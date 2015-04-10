#ifndef OPENGL4CONTEXT_H
#define OPENGL4CONTEXT_H

#include "Rendering/IContext.h"

#include <memory>

#include "Rendering/IBuffer.h"
#include "Rendering/IShader.h"
#include "Rendering/ITexture.h"
#include "Rendering/Reference.h"
#include "Rendering/ForwardDeclarations.h"
#include "OpenGL4VertexArray.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Context : public IContext
            {
                public:
                    OpenGL4Context();
                    virtual ~OpenGL4Context();

                    virtual void activate() override final;
                    virtual void deactivate() override final;

                    virtual bool isActive() const override final;

                    virtual bool isMultithreadingSupported() const override final;

                    virtual bool tryLock(const Reference<IBindable> &bindable) override final;
                    virtual void lock(const Reference<IBindable> &bindable) override final;
                    virtual void unlock(const Reference<IBindable> &bindable) override final;

                    virtual Reference<IBuffer> createHardwareBuffer(IBuffer::Type type) override final;
                    virtual Reference<IRenderTarget> createRenderTarget() override final;
                    virtual Reference<IShader> createShader(IShader::Type type) override final;
                    virtual Reference<IProgram> createProgram() override final;
                    virtual Reference<ITexture> createTexture(ITexture::Type type, ITexture::DataFormat dataFormat = ITexture::DataFormat::RGBA8) override final;

                    virtual Reference<IRenderTarget> getDefaultRenderTarget() override final;

                    Reference<OpenGL4VertexArray> getVertexArray(const IObject *object);
                    void createVertexArray(IObject *object);

                private:
                    class Private;
                    std::unique_ptr<Private> p;
            };
        }
    }
}

#endif // OPENGL4CONTEXT_H
