#include "Material.h"

namespace Amber
{
    namespace Rendering
    {
        Material::Material()
            : emission(0),
              translucency(0),
              reflectivity(0),
              indexOfRefraction(1),
              subsurfaceScattering(false)
        {
        }

        Core::IComponent::Type Material::getType() const
        {
            return Core::IComponent::Type::Material;
        }

        bool Material::isSetup() const
        {
            return true;
        }

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
            if (this->diffuseTexture.isValid())
            {
                this->diffuseTexture->setBindSlot(0);
            }
        }

        Reference<ITexture> Material::getNormalMap() const
        {
            return normalMap;
        }

        void Material::setNormalMap(const Reference<ITexture> &normalMap)
        {
            this->normalMap = normalMap;
            if (this->normalMap.isValid())
            {
                this->normalMap->setBindSlot(1);
            }
        }

        Reference<ITexture> Material::getSpecularMap() const
        {
            return specularMap;
        }

        void Material::setSpecularMap(const Reference<ITexture> &specularMap)
        {
            this->specularMap = specularMap;
            if (this->specularMap.isValid())
            {
                this->specularMap->setBindSlot(2);
            }
        }

        Reference<ITexture> Material::getDisplacementMap() const
        {
            return displacementMap;
        }

        void Material::setDisplacementMap(const Reference<ITexture> &displacementMap)
        {
            this->displacementMap = displacementMap;
            if (this->displacementMap.isValid())
            {
                this->displacementMap->setBindSlot(3);
            }
        }
    }
}
