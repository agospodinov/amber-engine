#include "Viewport.h"

namespace Amber
{
    namespace Rendering
    {
        int Viewport::getWidth() const
        {
            return width;
        }

        void Viewport::setWidth(int width)
        {
            this->width = width;
        }

        int Viewport::getHeight() const
        {
            return height;
        }

        void Viewport::setHeight(int height)
        {
            this->height = height;
        }

        void Viewport::setSize(int width, int height)
        {
            setWidth(width);
            setHeight(height);
        }
    }
}
