#include "Scene.h"

namespace Amber
{
    namespace Rendering
    {
        Scene::RenderMeshCollection &Scene::getMeshes()
        {
            return meshes;
        }

        Scene::RenderLightCollection &Scene::getLights()
        {
            return lights;
        }

        void Scene::addMesh(Scene::RenderMesh mesh)
        {
            this->meshes.push_back(std::move(mesh));
        }

        void Scene::addLight(Scene::RenderLight light)
        {
            this->lights.push_back(std::move(light));
        }
    }
}
