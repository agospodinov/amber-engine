#ifndef MESH_H
#define MESH_H

#include "IObject.h"

#include <memory>
#include <vector>

#include <Eigen/Core>

#include "Layout.h"
#include "Reference.h"
#include "VertexTypes.h"

#include "ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class Mesh : public IObject
        {
            public:
                Mesh();
                Mesh(const Mesh &other) = delete;
                Mesh(Mesh &&other) = default;
                virtual ~Mesh() = default;

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

                virtual const Eigen::Matrix4f &getLocalTransform() const override final;

                void setLayout(Layout layout);

                void setVertexCount(std::size_t vertexCount);
                void setPrimitiveCount(std::size_t primitiveCount);

            private:
                Reference<IBuffer> vertexBuffer;
                Reference<IBuffer> indexBuffer;
                Layout layout;
                std::size_t vertexCount;
                std::size_t primitiveCount;
                Eigen::Matrix4f localTransform;
        };
    }
}

#endif // MESH_H
