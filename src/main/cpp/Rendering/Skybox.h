#ifndef SKYBOX_H
#define SKYBOX_H

#include "IRenderable.h"

#include <memory>

#include "IProgram.h"
#include "ITexture.h"
#include "Material.h"
#include "Mesh.h"

namespace Amber
{
    namespace Rendering
    {
        class Skybox : public IRenderable
        {
            public:
                Skybox() = default;
                virtual ~Skybox() = default;

                virtual void setup(IRenderer *renderer);
                virtual void render(IRenderer *renderer);

            private:
                Mesh box;
                Material material;
        };
    }
}

#endif // SKYBOX_H
