#ifndef OPENGL4RENDERER_H
#define OPENGL4RENDERER_H

#include "Amber/Rendering/Backend/IRenderer.h"

#include <deque>

#include "Amber/Rendering/ForwardDeclarations.h"
#include "Amber/Rendering/Backend/OpenGL4/OpenGL4Includes.h"
#include "Amber/Rendering/Backend/OpenGL4/OpenGL4Context.h"

namespace Amber
{
    namespace Rendering
    {
        namespace GL4
        {
            class OpenGL4Renderer : public IRenderer
            {
                public:
                    OpenGL4Renderer();
                    virtual ~OpenGL4Renderer();

                    virtual void prepare(IObject &object) override final;
                    virtual void prepare(Reference<IProgram> program) override final;
                    virtual void prepare(Reference<ITexture> texture) override final;
                    virtual void prepare(Reference<IRenderTarget> renderTarget) override final;

                    virtual void render(Core::World &scene) override final;
                    virtual void render(IObject &object, Material &material) override final;

                    virtual void clear() override final;

                    virtual bool getRenderOption(RenderOption renderOption) const override final;
                    virtual void setRenderOption(RenderOption renderOption, bool enabled) override final;

                    virtual IContext &getContext() override final;

                private:
                    GLenum getRenderOptionId(IRenderer::RenderOption renderOption) const;

                    OpenGL4Context context;
            };
        }
    }
}

#endif // OPENGL4RENDERER_H
