#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Amber/Rendering/Camera.h"

namespace Amber
{
    namespace Rendering
    {
        class Viewport
        {
            public:
                Viewport() = default;

                int getWidth() const;
                int getHeight() const;

                Camera *getCamera() const;
                void setCamera(Camera *camera);

                void resize(int width, int height);

            private:
                Camera *camera;

                int width;
                int height;
        };
    }
}

#endif // VIEWPORT_H
