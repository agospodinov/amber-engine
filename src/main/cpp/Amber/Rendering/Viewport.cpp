#include "Viewport.h"

namespace Amber
{
    namespace Rendering
    {
        int Viewport::getWidth() const
        {
            return width;
        }

        int Viewport::getHeight() const
        {
            return height;
        }

        Camera *Viewport::getCamera() const
        {
            return camera;
        }

        void Viewport::setCamera(Camera *camera)
        {
            this->camera = camera;
        }

        void Viewport::resize(int width, int height)
        {
            this->width = width;
            this->height = height;

            if (camera != nullptr) {
                camera->setPerspectiveProjection(60.0f, static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
            }
        }
    }
}
