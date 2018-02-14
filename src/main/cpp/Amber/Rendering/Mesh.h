#ifndef MESH_H
#define MESH_H

#include "Amber/Core/IComponent.h"
#include "Amber/Rendering/IObject.h"

#include <memory>
#include <vector>

#include <Eigen/Core>

#include "Amber/Rendering/Layout.h"
#include "Amber/Rendering/Reference.h"
#include "Amber/Rendering/VertexTypes.h"

#include "Amber/Rendering/ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class Mesh : public IObject, public Core::IComponent
        {
            public:
                Mesh();
                Mesh(const Mesh &other) = delete;
                Mesh(Mesh &&other) = default;
                virtual ~Mesh() = default;

                Mesh &operator =(const Mesh &other) = delete;
                Mesh &operator =(Mesh &&other) noexcept = default;

                virtual Reference<IBuffer> &getVertexBuffer() override final;
                virtual const Reference<IBuffer> &getVertexBuffer() const override final;

                virtual Reference<IBuffer> &getIndexBuffer() override final;
                virtual const Reference<IBuffer> &getIndexBuffer() const override final;

                virtual Layout &getLayout() override final;

                virtual bool isInHardwareStorage() const override final;
                virtual void moveToHardwareStorage(IContext &context) override final;

                virtual std::size_t getVertexCount() const override final;
                virtual std::size_t getPrimitiveCount() const override final;
                virtual std::size_t getInstanceCount() const override final;

                void setLayout(Layout layout);

                void setVertexCount(std::size_t vertexCount);
                void setPrimitiveCount(std::size_t primitiveCount);

            private:
                Reference<IBuffer> vertexBuffer;
                Reference<IBuffer> indexBuffer;
                Layout layout;
                std::size_t vertexCount;
                std::size_t primitiveCount;
        };
    }
}

#endif // MESH_H
