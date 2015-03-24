#include "ImageTextureLoader.h"

#include "Utilities/Config.h"
#ifdef JPEG_FOUND

#define int_p_NULL (int*)NULL
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/gil/extension/io/tiff_io.hpp>
#undef int_p_NULL

#include "Rendering/ITexture.h"
#include "Rendering/Reference.h"

namespace Amber
{
    namespace IO
    {
        ImageTextureLoader::ImageTextureLoader()
        {
            imageExtensions = {
                { ".jpg",  ImageType::JPEG },
                { ".jpeg", ImageType::JPEG },
                { ".png",  ImageType::PNG  },
                { ".tiff", ImageType::TIFF }
            };
        }

        void ImageTextureLoader::loadTexture(const std::string &fileName, Rendering::Reference<Rendering::ITexture> &texture)
        {
            std::string path = "assets/graphics/textures/" + fileName;
            if (boost::filesystem::exists(path))
            {
                std::string extension = boost::filesystem::extension(path);
                boost::algorithm::to_lower(extension);
                ImageType imageType = imageExtensions.at(extension);

                boost::gil::rgb8_image_t image;
                switch (imageType)
                {
                    case ImageType::JPEG:
                        boost::gil::jpeg_read_image(path, image);
                        break;
                    case ImageType::PNG:
                        boost::gil::png_read_image(path, image);
                        break;
                    case ImageType::TIFF:
                        boost::gil::tiff_read_image(path, image);
                        break;
                    default:
                        throw std::runtime_error("Unsupported image type.");
                }

                // FIXME total hack
                if (texture->getType() == Rendering::ITexture::Type::TextureCube)
                {
                    texture->setSize(image.width(), image.height() / 6, 0);
                }
                else
                {
                    texture->setSize(image.width(), image.height(), 0);
                }

                unsigned char *data = boost::gil::interleaved_view_get_raw_data(boost::gil::view(image));
                texture->setImageData(Rendering::ITexture::DataMode::RGB, data);

                return;
            }

            throw std::runtime_error("Could not find texture: " + path);
        }
    }
}

#endif
