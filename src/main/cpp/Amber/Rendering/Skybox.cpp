#include "Skybox.h"

#include <functional>

#include "Amber/IO/ImageTextureLoader.h"
#include "IContext.h"
#include "IRenderer.h"
#include "Layout.h"
#include "Material.h"
#include "Mesh.h"
#include "RenderStage.h"
#include "ShaderPass.h"

namespace Amber
{
    namespace Rendering
    {
        Core::IComponent::Type Skybox::getType()
        {
            return model.getType();
        }

        bool Skybox::isSetup() const
        {
            return model.isSetup();
        }

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
            Mesh box;
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

            Material material;
            material.setDiffuseTexture(texture);

            model.addData(std::make_tuple(std::move(box), std::move(material)));
            model.setup(renderer);
        }

        void Skybox::render(IRenderer *renderer)
        {
            bool depthTestEnabled = renderer->getRenderOption(IRenderer::RenderOption::DepthTest);
            renderer->setRenderOption(IRenderer::RenderOption::DepthTest, false);
            model.render(renderer);
            renderer->setRenderOption(IRenderer::RenderOption::DepthTest, depthTestEnabled);
        }
    }
}
