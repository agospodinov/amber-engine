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
        template <>
        Layout Layout::getStandardLayout<Vertex::Position>()
        {
            Layout defaultLayout;
            *defaultLayout.attributes = {
                { "mdl_Position",  Vertex::Semantic::Coordinates        }
            };
            return defaultLayout;
        }

        template <>
        Layout Layout::getStandardLayout<Vertex::PositionNormal>()
        {
            Layout defaultLayout;
            *defaultLayout.attributes = {
                { "mdl_Position",  Vertex::Semantic::Coordinates        },
                { "mdl_Normal",    Vertex::Semantic::Normals            }
            };
            return defaultLayout;
        }

        template <>
        Layout Layout::getStandardLayout<Vertex::PositionNormalColor>()
        {
            Layout defaultLayout;
            *defaultLayout.attributes = {
                { "mdl_Position",  Vertex::Semantic::Coordinates        },
                { "mdl_Normal",    Vertex::Semantic::Normals            },
                { "mdl_Color",     Vertex::Semantic::Colors             }
            };
            return defaultLayout;
        }

        template <>
        Layout Layout::getStandardLayout<Vertex::PositionNormalUV>()
        {
            Layout defaultLayout;
            *defaultLayout.attributes = {
                { "mdl_Position",  Vertex::Semantic::Coordinates        },
                { "mdl_Normal",    Vertex::Semantic::Normals            },
                { "mdl_TexCoords", Vertex::Semantic::TextureCoordinates }
            };
            return defaultLayout;
        }

        std::int32_t Layout::getStandardBindLocation(Vertex::Semantic semantic)
        {
            return static_cast<unsigned int>(semantic);
        }

        Layout::Layout()
            : attributes(std::make_shared<AttributeMap>()),
              constants(std::make_shared<ConstantMap>())
        {
        }

        const Layout::AttributeMap &Layout::getAttributes() const
        {
            return *attributes;
        }

        const Layout::ConstantMap &Layout::getConstants() const
        {
            return *constants;
        }

        void Layout::insertAttribute(std::string name, Vertex::Semantic semantic)
        {
            attributes->emplace(name, semantic);
        }

        void Layout::insertConstant(std::string name, std::size_t location)
        {
            constants->emplace(name, location);
        }

        std::size_t Layout::getAttributeStride() const
        {
            std::size_t stride = 0;
            for (const auto &attribute : *attributes)
            {
                stride += Vertex::componentCount(attribute.second) * Vertex::componentStride(attribute.second);
            }
            return stride;
        }
    }
}
