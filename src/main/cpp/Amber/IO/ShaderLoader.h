#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Amber/Rendering/Backend/Reference.h"
#include "Amber/Rendering/Backend/IShader.h"

namespace Amber
{
    namespace IO
    {
        class ShaderLoader
        {
            public:
                ShaderLoader();

                void loadShader(const std::string &shaderName, Rendering::Reference<Rendering::IShader> &shader);

            private:
                std::map<Rendering::IShader::Type, std::vector<std::string>> shaderExtensions;

        };
    }
}

#endif // SHADERLOADER_H
