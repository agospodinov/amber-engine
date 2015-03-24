#include "Layout.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>

#include "VertexTypes.h"

namespace Amber
{
    namespace Rendering
    {
        Layout::Layout()
            : attributes(std::make_shared<AttributeList>())
        {
        }

        const Layout::AttributeList &Layout::getAttributes() const
        {
            return *attributes;
        }

        void Layout::insertAttribute(Attribute attribute)
        {
            attributes->push_back(attribute);
        }

        std::size_t Layout::getAttributeCount() const
        {
            return attributes->size();
        }

        std::size_t Layout::getOffset(std::size_t attributeIndex) const
        {
            if (attributeIndex < 0 || attributeIndex >= attributes->size())
            {
                throw std::out_of_range("Attribute index out of bounds");
            }

            std::size_t offset = 0;
            for (std::size_t i = 0; i < attributeIndex; i++)
            {
                const Attribute &attribute = attributes->at(i);
                offset += attribute.getCount() * attribute.getStride();
            }

            return offset;
        }

        std::size_t Layout::getTotalStride() const
        {
            std::size_t stride = 0;
            for (const Attribute &attribute : *attributes)
            {
                stride += attribute.getCount() * attribute.getStride();
            }
            return stride;
        }

        Layout::Attribute::Attribute(std::string name, Layout::ComponentType type, std::size_t count)
            : name(name),
              type(type),
              count(count)
        {
        }

        const std::string &Layout::Attribute::getName() const
        {
            return name;
        }

        Layout::ComponentType Layout::Attribute::getType() const
        {
            return type;
        }

        std::size_t Layout::Attribute::getCount() const
        {
            return count;
        }

        std::size_t Layout::Attribute::getStride() const
        {
            switch (type)
            {
                case ComponentType::Int8:
                case ComponentType::UInt8:
                    return 1;
                case ComponentType::Int16:
                case ComponentType::UInt16:
                    return 2;
                case ComponentType::Int32:
                case ComponentType::UInt32:
                case ComponentType::Float:
                    return 4;
                case ComponentType::Double:
                    return 8;
                default:
                    throw std::invalid_argument("Invalid component type.");
            }
        }
    }
}
