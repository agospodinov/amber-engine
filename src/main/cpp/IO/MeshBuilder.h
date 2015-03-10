#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#include <array>
#include <vector>
#include <utility>

#include <memory>

#include "Rendering/Mesh.h"

namespace Amber
{
    namespace IO
    {
        class MeshBuilder
        {
            public:
                MeshBuilder();
                ~MeshBuilder();

                void setPositions(const float *positions, std::size_t positionsCount);
                void setNormals(const float *normals, std::size_t normalsCount);
                void setColors(const float *colors, std::size_t colorsCount);
                void setTexCoords(const float *texCoords, std::size_t texCoordsCount);

                void setIndicesCount(std::size_t indicesCount);
                void setPositionIndices(const unsigned int *positionIndices);
                void setNormalIndices(const unsigned int *normalIndices);
                void setColorIndices(const unsigned int *colorIndices);
                void setTexCoordIndices(const unsigned int *texCoordIndices);

                Rendering::Mesh build();

            private:
                class Private;
                std::unique_ptr<Private> p;
        };
    }
}

#endif // MESHBUILDER_H
