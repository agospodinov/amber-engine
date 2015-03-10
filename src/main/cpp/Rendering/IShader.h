#ifndef ISHADER_H
#define ISHADER_H

#include <string>

namespace Amber
{
    namespace Rendering
    {
        class IShader
        {
            public:
                enum class Language
                {
                    HLSL,
                    GLSL,
                    Cg
                };

                enum class Type
                {
                    VertexShader,
                    PixelShader,
                    ComputeShader,
                    TesselationShader,
                    Other
                };

                IShader() = default;
                virtual ~IShader() = default;

                virtual void compile() = 0;
                virtual bool isCompiled() const = 0;

                virtual void setShaderSource(std::string shaderSource) = 0;

                virtual Language getLanguage() const = 0;
                virtual Type getType() const = 0;
        };
    }
}

#endif // ISHADER_H
