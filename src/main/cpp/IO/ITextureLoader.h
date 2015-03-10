#ifndef ITEXTURELOADER_H
#define ITEXTURELOADER_H

#include <memory>
#include <string>

#include "Rendering/ForwardDeclarations.h"

namespace Amber
{
    namespace IO
    {
        class ITextureLoader
        {
            public:
                ITextureLoader() = default;
                virtual ~ITextureLoader() = default;

                virtual void loadTexture(const std::string &fileName, Rendering::Reference<Rendering::ITexture> &texture) = 0;
        };
    }
}

#endif // ITEXTURELOADER_H
