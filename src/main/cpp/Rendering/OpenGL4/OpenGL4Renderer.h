#ifndef OPENGL4RENDERER_H
#define OPENGL4RENDERER_H

#include "Rendering/IRenderer.h"

#include <deque>

#include <GL/gl.h>

#include "Rendering/Procedure.h"
#include "Rendering/Scene.h"
#include "Rendering/Viewport.h"
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
                    virtual void prepare(Material &material) override final;
                    virtual void prepare(Reference<IProgram> program) override final;
                    virtual void prepare(Reference<ITexture> texture) override final;
                    virtual void prepare(Reference<IRenderTarget> renderTarget) override final;

                    virtual void render() override final;
                    virtual void render(IObject &object, Material &material) override final;

                    virtual void clear() override final;

                    virtual bool getRenderOption(RenderOption renderOption) const override final;
                    virtual void setRenderOption(RenderOption renderOption, bool enabled) override final;

                    virtual void handleWindowResize(int width, int height) override final;

                    virtual IContext &getContext() override final;
                    virtual Scene &getScene() override final;
                    virtual Viewport &getViewport() override final;

                private:
                    GLenum getRenderOptionId(IRenderer::RenderOption renderOption) const;

                    OpenGL4Context context;
                    Scene scene;
                    Viewport viewport;
            };
        }
    }
}

#endif // OPENGL4RENDERER_H
