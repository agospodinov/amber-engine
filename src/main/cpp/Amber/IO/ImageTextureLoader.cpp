#include "ImageTextureLoader.h"

#include "Amber/Utilities/Config.h"
#ifdef JPEG_FOUND

#define int_p_NULL (int*)NULL
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/extension/dynamic_image/any_image.hpp>
#include <boost/gil/extension/dynamic_image/any_image_view.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <boost/gil/extension/io/tiff_dynamic_io.hpp>
#include <boost/mpl/vector.hpp>
#undef int_p_NULL

#include "Amber/Rendering/ITexture.h"
#include "Amber/Rendering/Reference.h"

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
                { ".tiff", ImageType::TIFF },
                { ".tif",  ImageType::TIFF }
            };
        }

        void ImageTextureLoader::loadTexture(const std::string &fileName, Rendering::Reference<Rendering::ITexture> &texture)
        {
            using namespace boost::gil;

            std::string path = "assets/graphics/textures/" + fileName;
            if (!boost::filesystem::exists(path))
            {
                throw std::runtime_error("Could not find texture: " + path);
            }

            std::string extension = boost::filesystem::extension(path);
            boost::algorithm::to_lower(extension);
            ImageType imageType = imageExtensions.at(extension);

            typedef boost::mpl::vector<rgba8_image_t, rgba16_image_t, rgb8_image_t, rgb16_image_t> SupportedTypes;
            any_image<SupportedTypes> loadedImage;
            switch (imageType)
            {
                case ImageType::JPEG:
                    jpeg_read_image(path, loadedImage);
                    break;
                case ImageType::PNG:
                    png_read_image(path, loadedImage);
                    break;
                case ImageType::TIFF:
                    tiff_read_image(path, loadedImage);
                    break;
                default:
                    throw std::runtime_error("Unsupported image type.");
            }

            // FIXME total hack
            if (texture->getType() == Rendering::ITexture::Type::TextureCube)
            {
                texture->setSize(loadedImage.width(), loadedImage.height() / 6, 0);
            }
            else
            {
                texture->setSize(loadedImage.width(), loadedImage.height(), 0);
            }

            rgba8_image_t finalImage(loadedImage.dimensions());
            copy_and_convert_pixels(const_view(loadedImage), view(finalImage));
            const unsigned char *data = interleaved_view_get_raw_data(const_view(finalImage));
            texture->setImageData(data);
        }
    }
}

#endif
