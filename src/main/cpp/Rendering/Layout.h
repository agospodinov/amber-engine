#ifndef LAYOUT_H
#define LAYOUT_H

#include <cstdint>
#include <map>
#include <memory>
#include <string>

#include "VertexTypes.h"

namespace Amber
{
    namespace Rendering
    {
        class Layout
        {
            public:
                typedef std::map<std::string, Vertex::Semantic> AttributeMap;
                typedef std::map<std::string, std::size_t> ConstantMap;

                template <typename T>
                static Layout getStandardLayout();
                static std::int32_t getStandardBindLocation(Vertex::Semantic semantic);

                Layout();
                ~Layout() = default;

                const AttributeMap &getAttributes() const;
                const ConstantMap &getConstants() const;

                void insertAttribute(std::string name, Vertex::Semantic semantic);
                void insertConstant(std::string name, std::size_t location);

                std::size_t getAttributeStride() const;

            private:
                std::shared_ptr<AttributeMap> attributes;
                std::shared_ptr<ConstantMap> constants;
        };
    }
}

#endif // LAYOUT_H
