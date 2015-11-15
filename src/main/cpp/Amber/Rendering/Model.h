#ifndef MODEL_H
#define MODEL_H

#include "Amber/Rendering/IRenderable.h"

#include <tuple>
#include <vector>

#include <Eigen/Core>

#include "Amber/Rendering/Mesh.h"
#include "Amber/Rendering/Material.h"

namespace Amber
{
    namespace Rendering
    {
        class Model : public IRenderable
        {
            public:
                typedef std::tuple<Mesh, Material> ModelData;

                Model();
                Model(const Model &other) = delete;
                Model(Model &&other) noexcept = default;
                virtual ~Model() = default;

                Model &operator =(const Model &other) = delete;
                Model &operator =(Model &&other) noexcept = default;

                virtual Type getType() override;
                virtual bool isSetup() const override;

                virtual void setup(IRenderer *renderer) override;
                virtual void render(IRenderer *renderer) override;

                const std::vector<ModelData> &getData() const;
                void addData(ModelData data);

            private:
                std::vector<ModelData> data;
                bool allDataSetup;
        };
    }
}

#endif // MODEL_H
