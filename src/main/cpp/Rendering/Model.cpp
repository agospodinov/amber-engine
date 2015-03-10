#include "Model.h"

#include "IRenderer.h"

namespace Amber
{
    namespace Rendering
    {
        void Model::setup(IRenderer *renderer)
        {
            for (ModelData &submodel : data)
            {
                renderer->prepare(std::get<0>(submodel));
                renderer->prepare(std::get<1>(submodel));
            }
        }

        void Model::render(IRenderer *renderer)
        {
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
        }
    }
}
