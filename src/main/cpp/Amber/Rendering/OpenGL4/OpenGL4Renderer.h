#ifndef OPENGL4RENDERER_H
#define OPENGL4RENDERER_H

#include "Amber/Rendering/IRenderer.h"

#include <deque>

#include <GL/gl.h>

#include "Amber/Rendering/Procedure.h"
#include "Amber/Rendering/Viewport.h"
#include "OpenGL4Context.h"

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

                    virtual void render(Core::Scene &scene) override final;
                    virtual void render(IObject &object, Material &material) override final;

                    virtual void clear() override final;

                    virtual bool getRenderOption(RenderOption renderOption) const override final;
                    virtual void setRenderOption(RenderOption renderOption, bool enabled) override final;

                    virtual Procedure &getProcedure() override final;
                    virtual const Procedure &getProcedure() const override final;
                    virtual void setProcedure(Procedure procedure) override final;

                    virtual IContext &getContext() override final;
                    virtual Viewport &getViewport() override final;

                private:
                    GLenum getRenderOptionId(IRenderer::RenderOption renderOption) const;

                    OpenGL4Context context;
                    Viewport viewport;
                    Procedure procedure;
            };
        }
    }
}

#endif // OPENGL4RENDERER_H
