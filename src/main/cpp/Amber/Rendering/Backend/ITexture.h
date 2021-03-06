#ifndef ITEXTURE_H
#define ITEXTURE_H

#include "Amber/Rendering/Backend/IMultiBindable.h"

#include <cstdint>
#include <cstdlib>

namespace Amber
{
    namespace Rendering
    {
        class ITexture : public IMultiBindable
        {
            public:
                enum class Type
                {
                    Texture1D,
                    Texture1DArray,
                    Texture2D,
                    Texture2DArray,
                    Texture3D,
                    TextureCube,
                    ImplementationDefined
                };

                enum class WrapMode
                {
                    Repeat,
                    MirroredRepeat,
                    ClampToEdge,
                    ClampToBorder
                };

                enum class FilterMode
                {
                    Nearest,
                    Linear
                };

                enum class DataFormat
                {
                    RGB8,
                    RGB16,
                    RGB16F,
                    RGB32F,
                    RGBA8,
                    RGBA16,
                    RGBA16F,
                    RGBA32F,
                    Depth32,
                    Depth24Stencil8
                };

                ITexture() = default;
                virtual ~ITexture() = default;

                virtual std::size_t getWidth() const = 0;
                virtual std::size_t getHeight() const = 0;
                virtual std::size_t getDepth() const = 0;

                virtual Type getType() const = 0;

                virtual void setSize(std::size_t width, std::size_t height, std::size_t depth) = 0;

                virtual void setImageData(const std::uint8_t *data) = 0;
                virtual void setFilterMode(FilterMode mode) = 0;
                virtual void setWrapMode(WrapMode mode) = 0;
        };
    }
}

#endif // ITEXTURE_H
