#include "ShaderPass.h"

namespace Amber
{
    namespace Rendering
    {
        ShaderPass::ShaderPass(Reference<IProgram> program)
            : program(program)
        {
        }

        Reference<IProgram> ShaderPass::getProgram() const
        {
            return program;
        }
    }
}
