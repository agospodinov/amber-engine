#include "Model.h"

#include "IRenderer.h"

namespace Amber
{
    namespace Rendering
    {
        Model::Model()
            : allDataSetup(false)
        {
        }

        Core::IComponent::Type Model::getType()
        {
            return IComponent::Type::Model;
        }

        bool Model::isSetup() const
        {
            return allDataSetup;
        }


        void Model::setup(IRenderer *renderer)
        {
            for (ModelData &submodel : data)
            {
                renderer->prepare(std::get<0>(submodel));

                Material &material = std::get<1>(submodel);

                if (material.getDiffuseTexture().isValid())
                {
                    renderer->prepare(material.getDiffuseTexture());
                }

                if (material.getNormalMap().isValid())
                {
                    renderer->prepare(material.getNormalMap());
                }

                if (material.getSpecularMap().isValid())
                {
                    renderer->prepare(material.getSpecularMap());
                }

                if (material.getDisplacementMap().isValid())
                {
                    renderer->prepare(material.getDisplacementMap());
                }
            }

            this->allDataSetup = true;
        }

        void Model::render(IRenderer *renderer)
        {
            // TODO sort data by material and use indirect rendering
            for (ModelData &submodel : data)
            {
                renderer->render(std::get<0>(submodel), std::get<1>(submodel));
            }
        }

        const std::vector<Model::ModelData> &Model::getData() const
        {
            return data;
        }

        void Model::addData(ModelData data)
        {
            this->data.push_back(std::move(data));
            this->allDataSetup = false;
        }
    }
}
