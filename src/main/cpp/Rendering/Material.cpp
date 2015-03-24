#include "Material.h"

namespace Amber
{
    namespace Rendering
    {
        float Material::getEmission() const
        {
            return emission;
        }

        void Material::setEmission(float emission)
        {
            this->emission = emission;
        }

        float Material::getTranslucency() const
        {
            return translucency;
        }

        void Material::setTranslucency(float translucency)
        {
            this->translucency = translucency;
        }

        float Material::getReflectivity() const
        {
            return reflectivity;
        }

        void Material::setReflectivity(float reflectivity)
        {
            this->reflectivity = reflectivity;
        }

        float Material::getIndexOfRefraction() const
        {
            return indexOfRefraction;
        }

        void Material::setIndexOfRefraction(float indexOfRefraction)
        {
            this->indexOfRefraction = indexOfRefraction;
        }

        Reference<ITexture> Material::getDiffuseTexture() const
        {
            return diffuseTexture;
        }

        void Material::setDiffuseTexture(const Reference<ITexture> &diffuseTexture)
        {
            this->diffuseTexture = diffuseTexture;
        }

        Reference<ITexture> Material::getNormalMap() const
        {
            return normalMap;
        }

        void Material::setNormalMap(const Reference<ITexture> &normalMap)
        {
            this->normalMap = normalMap;
        }

        Reference<ITexture> Material::getSpecularMap() const
        {
            return specularMap;
        }

        void Material::setSpecularMap(const Reference<ITexture> &specularMap)
        {
            this->specularMap = specularMap;
        }

        Reference<ITexture> Material::getDisplacementMap() const
        {
            return displacementMap;
        }

        void Material::setDisplacementMap(const Reference<ITexture> &displacementMap)
        {
            this->displacementMap = displacementMap;
        }
    }
}
