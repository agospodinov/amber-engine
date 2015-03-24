#ifndef IMAGETEXTURELOADER_H
#define IMAGETEXTURELOADER_H

#include "Utilities/Config.h"
#ifdef JPEG_FOUND

#include "ITextureLoader.h"

#include <map>
#include <memory>

namespace Amber
{
    namespace IO
    {
        class ImageTextureLoader : public ITextureLoader
        {
            public:
                ImageTextureLoader();
                virtual ~ImageTextureLoader() = default;

                virtual void loadTexture(const std::string &fileName, Rendering::Reference<Rendering::ITexture> &texture) override final;

            private:
                enum class ImageType
                {
                    JPEG,
                    PNG,
                    TIFF
                };

                std::map<std::string, ImageType> imageExtensions;
        };
    }
}

#endif

#endif // IMAGETEXTURELOADER_H
