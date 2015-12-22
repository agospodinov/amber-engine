#ifndef SKYBOX_H
#define SKYBOX_H

#include "Amber/Rendering/IRenderable.h"

#include <memory>

#include "Amber/Rendering/IProgram.h"
#include "Amber/Rendering/ITexture.h"
#include "Amber/Rendering/Material.h"
#include "Amber/Rendering/Mesh.h"

namespace Amber
{
    namespace Rendering
    {
        class Skybox : public IRenderable
        {
            public:
                Skybox() = default;
                virtual ~Skybox() = default;

                virtual Type getType();
                virtual bool isSetup() const;

                virtual void setup(IRenderer *renderer);
                virtual void render(IRenderer *renderer);

            private:
                Mesh box;
                Material material;
        };
    }
}

#endif // SKYBOX_H
