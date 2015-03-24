#ifndef SHADERPASS_H
#define SHADERPASS_H

#include "IProgram.h"
#include "Reference.h"

#include "ForwardDeclarations.h"

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

                void setup(IRenderer *renderer);

            private:
                Reference<IProgram> program;
        };
    }
}

#endif // SHADERPASS_H
