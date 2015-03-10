#ifndef SHADERPASS_H
#define SHADERPASS_H

#include "IProgram.h"
#include "Node.h"
#include "Reference.h"

#include "ForwardDeclarations.h"

namespace Amber
{
    namespace Rendering
    {
        class ShaderPass
        {
            public:
                ShaderPass(Reference<IProgram> program, Node::Type filterType, std::function<bool(IRenderable *)> renderPredicate = nullptr);
                ShaderPass(const ShaderPass &other) = delete;
                ShaderPass(ShaderPass &&other) = default;
                ~ShaderPass() = default;

                ShaderPass &operator =(const ShaderPass &other) = delete;
                ShaderPass &operator =(ShaderPass &&other) = default;

                void setup(IRenderer *renderer);
                void render(IRenderer *renderer);

            private:
                Reference<IProgram> program;
                Node::Type filterType;
                std::function<bool(IRenderable *)> renderPredicate;
        };
    }
}

#endif // SHADERPASS_H
