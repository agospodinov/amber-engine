#ifndef VERTEXTYPES_H
#define VERTEXTYPES_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace Amber
{
    namespace Rendering
    {
        namespace Vertex
        {
            struct PositionNormalUV
            {
                    float x, y, z;
                    float nx, ny, nz;
                    float u, v;
            };

            struct PositionNormalColor
            {
                    float x, y, z;
                    float nx, ny, nz;
                    std::uint8_t r, g, b, a;
            };

            struct PositionNormal
            {
                    float x, y, z;
                    float nx, ny, nz;
            };

            struct Position
            {
                    float x, y, z;
            };

            enum class Semantic : unsigned int
            {
                Coordinates = 0,
                Normals = 1,
                Colors = 2,
                TextureCoordinates = 3
            };

            constexpr std::size_t attributeOffset(Semantic attribute)
            {
                return /*(attribute == Semantic::Coordinates) ? offsetof(Position, x)
                     : (attribute == Semantic::Normals) ? offsetof(PositionNormal, nx)
                     : (attribute == Semantic::Colors) ? offsetof(PositionNormalColor, r)
                     : (attribute == Semantic::TextureCoordinates) ? offsetof(PositionNormalUV, u)
                     : */0;
            }

            constexpr unsigned int componentCount(Semantic attribute)
            {
                return /*(attribute == Semantic::Coordinates) ? 3
                     : (attribute == Semantic::Normals) ? 3
                     : (attribute == Semantic::Colors) ? 4
                     : (attribute == Semantic::TextureCoordinates) ? 2
                     : */0;
            }

            constexpr unsigned int componentStride(Semantic attribute)
            {
                return /*(attribute == Semantic::Coordinates) ? 4
                     : (attribute == Semantic::Normals) ? 4
                     : (attribute == Semantic::Colors) ? 1
                     : (attribute == Semantic::TextureCoordinates) ? 4
                     : */0;
            }

            constexpr unsigned int componentType(Semantic attribute)
            {
                return /*(attribute == Semantic::Coordinates) ? GL_FLOAT
                     : (attribute == Semantic::Normals) ? GL_FLOAT
                     : (attribute == Semantic::Colors) ? GL_UNSIGNED_BYTE
                     : (attribute == Semantic::TextureCoordinates) ? GL_FLOAT
                     : */0;
            }

            template <typename T>
            struct IsVertexType : std::integral_constant<bool,
                    std::is_same<PositionNormalUV, typename std::remove_cv<T>::type>::value ||
                    std::is_same<PositionNormalColor, typename std::remove_cv<T>::type>::value ||
                    std::is_same<PositionNormal, typename std::remove_cv<T>::type>::value ||
                    std::is_same<Position, typename std::remove_cv<T>::type>::value>
            {
            };
        }
    }
}

#include "VertexTypes.txx"

#endif // VERTEXTYPES_H
