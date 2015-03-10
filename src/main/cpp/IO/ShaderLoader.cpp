#include "ShaderLoader.h"

#include <cassert>
#include <fstream>

#include "Rendering/Reference.h"
#include "AssetManager.h"

namespace Amber
{
    namespace IO
    {
        ShaderLoader::ShaderLoader()
        {
            shaderExtensions = {
                { Rendering::IShader::Type::VertexShader,      { "vsh", "vert" }           },
                { Rendering::IShader::Type::PixelShader,       { "psh", "fsh", "frag" }    },
                { Rendering::IShader::Type::ComputeShader,     { "csh", "comp" }           },
                { Rendering::IShader::Type::TesselationShader, { "tsh", "tess" }           },
                { Rendering::IShader::Type::Other,             { "gsh", "glsl", "hlsl" }   }
            };
        }

        void ShaderLoader::loadShader(const std::string &shaderName, Rendering::Reference<Rendering::IShader> &shader)
        {
            assert(shader.isValid());

            std::string language;
            switch (shader->getLanguage())
            {
                case Rendering::IShader::Language::HLSL:
                    language = "HLSL";
                    break;
                case Rendering::IShader::Language::GLSL:
                    language = "GLSL";
                    break;
                case Rendering::IShader::Language::Cg:
                    language = "Cg";
                    break;
            }

            for (const std::string &extension : shaderExtensions.at(shader->getType()))
            {
                std::string path = "assets/graphics/shaders/" + language + "/" + shaderName + "." + extension;
//                if (boost::filesystem::exists(path))
                {
                    std::ifstream inputFile(path);
                    if (!inputFile.is_open())
                    {
                        throw std::runtime_error("Could not read shader file.");
                    }

                    std::string shaderCode;
                    shaderCode.assign(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>());

                    shader->setShaderSource(shaderCode);

                    return;
                }
            }

            throw std::runtime_error("Could not find shader: " + shaderName);
        }
    }
}
