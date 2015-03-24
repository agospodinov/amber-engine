#include "Skybox.h"

#include <functional>

#include "IO/ImageTextureLoader.h"
#include "IContext.h"
#include "IRenderer.h"
#include "Layout.h"
#include "Node.h"
#include "RenderStage.h"
#include "ShaderPass.h"

namespace Amber
{
    namespace Rendering
    {
        void Skybox::setup(IRenderer *renderer)
        {
            const float distance = 1.0f;

            std::vector<float> positions = {
                -distance, -distance, -distance,
                -distance, -distance,  distance,
                -distance,  distance, -distance,
                -distance,  distance,  distance,
                 distance, -distance, -distance,
                 distance, -distance,  distance,
                 distance,  distance, -distance,
                 distance,  distance,  distance
            };

            std::vector<std::uint32_t> indices = {
                2, 0, 4,
                4, 6, 2,

                1, 0, 2,
                2, 3, 1,

                4, 5, 7,
                7, 6, 4,

                1, 3, 7,
                7, 5, 1,

                2, 6, 7,
                7, 3, 2,

                0, 1, 4,
                4, 1, 5
            };

            Layout layout;
            layout.insertAttribute(Layout::Attribute("mdl_Position", Layout::ComponentType::Float, 3));
            box.setLayout(layout);

            box.getVertexBuffer()->resize(positions.size() * sizeof(float));
            box.getVertexBuffer()->assign(0, positions.size() * sizeof(float), positions.data());

            box.getIndexBuffer()->resize(indices.size() * sizeof(std::uint32_t));
            box.getIndexBuffer()->assign(0, indices.size() * sizeof(std::uint32_t), indices.data());

            box.setVertexCount(positions.size());
            box.setPrimitiveCount(indices.size());

            Reference<ITexture> texture = renderer->getContext().createTexture(ITexture::Type::TextureCube);
//            IO::ImageTextureLoader textureLoader;
//            textureLoader.loadTexture("Skybox.jpg", texture); // FIXME I don't like this being hardcoded
            texture->setWrapMode(ITexture::WrapMode::ClampToEdge);

            material.setDiffuseTexture(texture);

            renderer->prepare(box);
            renderer->prepare(material);
        }

        void Skybox::render(IRenderer *renderer)
        {
            bool depthTestEnabled = renderer->getRenderOption(IRenderer::RenderOption::DepthTest);
            renderer->setRenderOption(IRenderer::RenderOption::DepthTest, false);
            renderer->render(box, material);
            renderer->setRenderOption(IRenderer::RenderOption::DepthTest, depthTestEnabled);
        }
    }
}
