#include "Mesh.h"

#include "IBuffer.h"
#include "IContext.h"

namespace Amber
{
    namespace Rendering
    {
        Mesh::Mesh()
            : vertexCount(0),
              primitiveCount(0),
              localTransform(Eigen::Matrix4f::Identity())
        {
            // FIXME I'd rather we didn't depend on an active context in this constructor
            auto context = IContext::getActiveContext();
            if (context != nullptr)
            {
                vertexBuffer = context->createHardwareBuffer(IBuffer::Type::Vertex);
                indexBuffer = context->createHardwareBuffer(IBuffer::Type::Index);
            }
        }

        Reference<IBuffer> &Mesh::getVertexBuffer()
        {
            return vertexBuffer;
        }

        const Reference<IBuffer> &Mesh::getVertexBuffer() const
        {
            return vertexBuffer;
        }

        Reference<IBuffer> &Mesh::getIndexBuffer()
        {
            return indexBuffer;
        }

        const Reference<IBuffer> &Mesh::getIndexBuffer() const
        {
            return indexBuffer;
        }

        std::shared_ptr<Layout> &Mesh::getLayout()
        {
            return layout;
        }

        bool Mesh::isInHardwareStorage() const
        {
            return vertexBuffer.cast<IBuffer>().isValid();
        }

        void Mesh::moveToHardwareStorage(IContext &context)
        {
            if (isInHardwareStorage())
            {
                //                    Utilities::Logger log;
                //                    log.warning("Mesh asked to move to hardware storage multiple times");
                assert(false);
                return;
            }

            Reference<IBuffer> vertexBuffer = context.createHardwareBuffer(IBuffer::Type::Vertex);
            this->vertexBuffer->migrate(*vertexBuffer);

            Reference<IBuffer> indexBuffer = context.createHardwareBuffer(IBuffer::Type::Index);
            this->indexBuffer->migrate(*indexBuffer);

            this->vertexBuffer = std::move(vertexBuffer);
            this->indexBuffer = std::move(indexBuffer);
        }

        std::size_t Mesh::getVertexCount() const
        {
            return vertexCount;
        }

        std::size_t Mesh::getPrimitiveCount() const
        {
            return primitiveCount;
        }

        std::size_t Mesh::getInstanceCount() const
        {
            return 1;
        }

        const Eigen::Matrix4f &Mesh::getLocalTransform() const
        {
            return localTransform;
        }

        void Mesh::setLayout(std::shared_ptr<Layout> layout)
        {
            this->layout = std::move(layout);
        }

        void Mesh::setVertexCount(std::size_t vertexCount)
        {
            this->vertexCount = vertexCount;
        }

        void Mesh::setPrimitiveCount(std::size_t primitiveCount)
        {
            this->primitiveCount = primitiveCount;
        }
    }
}
