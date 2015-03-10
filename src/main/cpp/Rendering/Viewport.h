#ifndef VIEWPORT_H
#define VIEWPORT_H

namespace Amber
{
    namespace Rendering
    {
        class Viewport
        {
            public:
                Viewport() = default;

                int getWidth() const;
                void setWidth(int width);

                int getHeight() const;
                void setHeight(int height);

                void setSize(int width, int height);

            private:
                int width;
                int height;
        };
    }
}

#endif // VIEWPORT_H
