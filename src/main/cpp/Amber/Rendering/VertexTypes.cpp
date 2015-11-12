#include "VertexTypes.h"

#include <algorithm>
#include <cstring>

namespace Amber
{
    namespace Rendering
    {
        VertexArray::VertexArray(Reference<IBuffer> buffer, Layout layout)
            : data(buffer->data()),
              layout(std::move(layout))
        {
        }

        VertexComponentArray VertexArray::get(const std::string &name) const
        {
            const Layout::Attribute *attribute;
            const Layout::AttributeList &attributes = layout.getAttributes();
            std::size_t index;

            for (index = 0; index < layout.getAttributeCount(); index++)
            {
                if (attributes.at(index).getName() == name)
                {
                    attribute = &attributes.at(index);
                    break;
                }
            }

            if (index == layout.getAttributeCount())
            {
                return VertexComponentArray(nullptr, nullptr, 0);
            }

            // TODO fix compiler warning
            return VertexComponentArray(static_cast<std::uint8_t *>(data.get()) + layout.getOffset(index), attribute, layout.getTotalStride());
        }

        VertexComponentArray::VertexComponentArray(std::uint8_t *subdata, const Layout::Attribute *attribute, std::size_t totalStride)
            : subdata(subdata),
              attribute(attribute),
              totalStride(totalStride)
        {
        }

        bool VertexComponentArray::isValid() const
        {
            return subdata != nullptr;
        }

        Vertex VertexComponentArray::at(std::size_t index)
        {
            return Vertex(subdata + index * totalStride, attribute);
        }

        Vertex::Vertex(std::uint8_t *vertexData, const Layout::Attribute *attribute)
            : vertexData(vertexData),
              attribute(attribute)
        {
        }

        template <typename InputType>
        void Vertex::optimalCopy(const InputType *inputData, Layout::ComponentType inputType)
        {
            if (inputType == attribute->getType())
            {
                std::memcpy(vertexData, inputData, attribute->getCount() * attribute->getStride());
            }
            else
            {
                switch (attribute->getType())
                {
                    case Layout::ComponentType::Float:
                        transform<InputType, float>(inputData);
                        break;
                    case Layout::ComponentType::Double:
                        transform<InputType, double>(inputData);
                        break;
                    case Layout::ComponentType::Int8:
                        transform<InputType, std::int8_t>(inputData);
                        break;
                    case Layout::ComponentType::Int16:
                        transform<InputType, std::int16_t>(inputData);
                        break;
                    case Layout::ComponentType::Int32:
                        transform<InputType, std::int32_t>(inputData);
                        break;
                    case Layout::ComponentType::UInt8:
                        transform<InputType, std::uint8_t>(inputData);
                        break;
                    case Layout::ComponentType::UInt16:
                        transform<InputType, std::uint16_t>(inputData);
                        break;
                    case Layout::ComponentType::UInt32:
                        transform<InputType, std::uint32_t>(inputData);
                        break;
                    default:
                        break;
                }
            }
        }

        template <typename InputType, typename DestinationType>
        void Vertex::transform(const InputType *data)
        {
            std::transform(data, data + attribute->getCount(), reinterpret_cast<DestinationType *>(vertexData), [](InputType item) -> DestinationType
            {
                return static_cast<DestinationType>(item);
            });
        }

        void Vertex::copyFrom(const float *data)
        {
            optimalCopy(data, Layout::ComponentType::Float);
        }

        void Vertex::copyFrom(const double *data)
        {
            optimalCopy(data, Layout::ComponentType::Double);
        }

        void Vertex::copyFrom(const int8_t *data)
        {
            optimalCopy(data, Layout::ComponentType::Int8);
        }

        void Vertex::copyFrom(const int16_t *data)
        {
            optimalCopy(data, Layout::ComponentType::Int16);
        }

        void Vertex::copyFrom(const int32_t *data)
        {
            optimalCopy(data, Layout::ComponentType::Int32);
        }

        void Vertex::copyFrom(const uint8_t *data)
        {
            optimalCopy(data, Layout::ComponentType::UInt8);
        }

        void Vertex::copyFrom(const uint16_t *data)
        {
            optimalCopy(data, Layout::ComponentType::UInt16);
        }

        void Vertex::copyFrom(const uint32_t *data)
        {
            optimalCopy(data, Layout::ComponentType::UInt32);
        }
    }
}
