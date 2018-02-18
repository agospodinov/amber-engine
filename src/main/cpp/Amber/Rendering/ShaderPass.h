#ifndef SHADERPASS_H
#define SHADERPASS_H

#include "Amber/Rendering/Backend/IProgram.h"
#include "Amber/Rendering/Backend/Reference.h"

#include "Amber/Rendering/ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class ShaderPass
        {
            public:
                ShaderPass(Reference<IProgram> program);
                ShaderPass(const ShaderPass &other) = default;
                ShaderPass(ShaderPass &&other) noexcept = default;
                ~ShaderPass() = default;

                ShaderPass &operator =(const ShaderPass &other) = default;
                ShaderPass &operator =(ShaderPass &&other) noexcept = default;

                Reference<IProgram> getProgram() const;

            private:
                Reference<IProgram> program;
        };
    }
}

#endif // SHADERPASS_H
