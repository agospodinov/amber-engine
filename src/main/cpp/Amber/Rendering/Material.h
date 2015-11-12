#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>

#include "Amber/Rendering/IProgram.h"
#include "Amber/Rendering/Layout.h"

namespace Amber
{
    namespace Rendering
    {
        class Material
        {
            public:
                Material() = default;
                ~Material() = default;

                float getEmission() const;
                void setEmission(float emission);

                float getTranslucency() const;
                void setTranslucency(float translucency);

                float getReflectivity() const;
                void setReflectivity(float reflectivity);

                float getIndexOfRefraction() const;
                void setIndexOfRefraction(float indexOfRefraction);

                Reference<ITexture> getDiffuseTexture() const;
                void setDiffuseTexture(const Reference<ITexture> &diffuseTexture);

                Reference<ITexture> getNormalMap() const;
                void setNormalMap(const Reference<ITexture> &normalMap);

                Reference<ITexture> getSpecularMap() const;
                void setSpecularMap(const Reference<ITexture> &specularMap);

                Reference<ITexture> getDisplacementMap() const;
                void setDisplacementMap(const Reference<ITexture> &displacementMap);

            private:
                float emission;
                float translucency;
                float reflectivity;
                float indexOfRefraction;

                Reference<ITexture> diffuseTexture;
                Reference<ITexture> normalMap;
                Reference<ITexture> specularMap;
                Reference<ITexture> displacementMap;
        };
    }
}

#endif // MATERIAL_H
