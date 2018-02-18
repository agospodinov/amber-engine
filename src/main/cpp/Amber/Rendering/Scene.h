#ifndef SCENE_H
#define SCENE_H

#include "Amber/Core/Entity.h"
#include "Amber/Core/Transform.h"
#include "Amber/Rendering/Mesh.h"
#include "Amber/Rendering/Material.h"
#include "Amber/Rendering/Light.h"

namespace Amber
{
    namespace Rendering
    {
        class Scene
        {
            public:
                typedef Core::Entity::Proxy<Mesh, Material, Core::Transform> RenderMesh;
                typedef Core::Entity::Proxy<Light, Core::Transform> RenderLight;

                typedef std::vector<RenderMesh> RenderMeshCollection;
                typedef std::vector<RenderLight> RenderLightCollection;

                Scene() = default;
                ~Scene() = default;

                RenderMeshCollection &getMeshes();
                RenderLightCollection &getLights();

                void addMesh(RenderMesh mesh);
                void addLight(RenderLight light);

            private:
                RenderMeshCollection meshes;
                RenderLightCollection lights;
        };
    }
}

#endif // SCENE_H
