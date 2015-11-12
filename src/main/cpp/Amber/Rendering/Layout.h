#ifndef LAYOUT_H
#define LAYOUT_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace Amber
{
    namespace Rendering
    {
        class Layout
        {
            public:
                enum class ComponentType
                {
                    Float,
                    Double,
                    Int8,
                    Int16,
                    Int32,
                    UInt8,
                    UInt16,
                    UInt32
                };

                enum class Ordering
                {
                    StructureOfArrays,
                    ArrayOfStructures
                };

                struct Attribute
                {
                    public:
                        Attribute(std::string name, ComponentType type, std::size_t count);

                        const std::string &getName() const;
                        ComponentType getType() const;
                        std::size_t getCount() const;
                        std::size_t getStride() const;

                    private:
                        std::string name;
                        ComponentType type;
                        std::size_t count;
                };

                typedef std::vector<Attribute> AttributeList;

                Layout();
                ~Layout() = default;

                const AttributeList &getAttributes() const;

                void insertAttribute(Attribute attribute);

                std::size_t getAttributeCount() const;
                std::size_t getOffset(std::size_t attributeIndex) const;
                std::size_t getTotalStride() const;

            private:
                std::shared_ptr<AttributeList> attributes;
        };
    }
}

#endif // LAYOUT_H
