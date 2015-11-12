#ifndef IRENDERER_H
#define IRENDERER_H

#include <deque>

#include "Amber/Rendering/ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class IRenderer
        {
            public:
                enum class RenderOption
                {
                    Culling,
                    DepthTest,
                    StencilTest
                };

                IRenderer() = default;
                virtual ~IRenderer() = default;

                virtual void prepare(IObject &object) = 0;
                virtual void prepare(Material &material) = 0;
                virtual void prepare(Reference<IProgram> program) = 0;
                virtual void prepare(Reference<ITexture> texture) = 0;
                virtual void prepare(Reference<IRenderTarget> renderTarget) = 0;

                virtual void render() = 0;
                virtual void render(IObject &renderable, Material &material) = 0;

                virtual void clear() = 0;

                virtual bool getRenderOption(RenderOption renderOption) const = 0;
                virtual void setRenderOption(RenderOption renderOption, bool enabled) = 0;

                virtual void handleWindowResize(int width, int height) = 0;

                virtual IContext &getContext() = 0;
                virtual Scene &getScene() = 0;
                virtual Viewport &getViewport() = 0;
        };
    }
}

#endif // IRENDERER_H
