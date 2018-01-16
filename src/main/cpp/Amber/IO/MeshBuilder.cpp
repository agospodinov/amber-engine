#include "MeshBuilder.h"

#include <map>
#include <numeric>

namespace Amber
{
    namespace IO
    {
        class MeshBuilder::Private
        {
            public:
                Private();

                std::vector<std::uint32_t> reindex();

                void buildVertexArray(Rendering::Mesh &mesh) const;

                const float *positions;
                std::size_t positionsCount;
                const unsigned int *positionIndices;

                const float *normals;
                std::size_t normalsCount;
                const unsigned int *normalIndices;

                const float *colors;
                std::size_t colorsCount;
                const unsigned int *colorIndices;

                const float *texCoords;
                std::size_t texCoordsCount;
                const unsigned int *texCoordIndices;

                std::size_t indicesCount;
                std::map<std::array<std::size_t, 4>, std::uint32_t> indexMap;
        };

        MeshBuilder::MeshBuilder()
            : p(new Private())
        {
        }

        MeshBuilder::~MeshBuilder()
        {
        }

        void MeshBuilder::setPositions(const float *positions, std::size_t positionsCount)
        {
            p->positions = positions;
            p->positionsCount = positionsCount;
        }

        void MeshBuilder::setNormals(const float *normals, std::size_t normalsCount)
        {
            p->normals = normals;
            p->normalsCount = normalsCount;
        }

        void MeshBuilder::setColors(const float *colors, std::size_t colorsCount)
        {
            p->colors = colors;
            p->colorsCount = colorsCount;
        }

        void MeshBuilder::setTexCoords(const float *texCoords, std::size_t texCoordsCount)
        {
            p->texCoords = texCoords;
            p->texCoordsCount = texCoordsCount;
        }

        void MeshBuilder::setIndicesCount(std::size_t indicesCount)
        {
            p->indicesCount = indicesCount;
        }

        void MeshBuilder::setPositionIndices(const unsigned int *positionIndices)
        {
            p->positionIndices = positionIndices;
        }

        void MeshBuilder::setNormalIndices(const unsigned int *normalIndices)
        {
            p->normalIndices = normalIndices;
        }

        void MeshBuilder::setColorIndices(const unsigned int *colorIndices)
        {
            p->colorIndices = colorIndices;
        }

        void MeshBuilder::setTexCoordIndices(const unsigned int *texCoordIndices)
        {
            p->texCoordIndices = texCoordIndices;
        }

        Rendering::Mesh MeshBuilder::build()
        {
            using namespace Rendering;

            Mesh mesh;

            std::vector<std::uint32_t> indices = p->reindex();
            if (mesh.getIndexBuffer().isValid())
            {
                Reference<IBuffer> &indexBuffer = mesh.getIndexBuffer();
                indexBuffer->resize(indices.size() * sizeof(std::uint32_t));
                indexBuffer->assign(0, indices.size() * sizeof(std::uint32_t), indices.data());
            }

            Layout layout;

            // FIXME un-hardcode
            if (p->positions)
            {
                layout.insertAttribute(Layout::Attribute("mdl_Position", Layout::ComponentType::Float, 3));
            }
            else
            {
                throw std::runtime_error("Trying to build a mesh with no position array.");
            }

            if (p->normals)
            {
                layout.insertAttribute(Layout::Attribute("mdl_Normal", Layout::ComponentType::Float, 3));
            }

            if (p->colors)
            {
                layout.insertAttribute(Layout::Attribute("mdl_Color", Layout::ComponentType::UInt8, 3));
            }

            if (p->texCoords)
            {
                layout.insertAttribute(Layout::Attribute("mdl_TexCoords", Layout::ComponentType::Float, 2));
            }

            mesh.setLayout(layout);
            p->buildVertexArray(mesh);

            return mesh;
        }

        MeshBuilder::Private::Private()
            : positions(nullptr),
              positionsCount(0),
              positionIndices(nullptr),
              normals(nullptr),
              normalsCount(0),
              normalIndices(nullptr),
              colors(nullptr),
              colorsCount(0),
              colorIndices(nullptr),
              texCoords(nullptr),
              texCoordsCount(0),
              texCoordIndices(nullptr),
              indicesCount(0)
        {
        }

        std::vector<std::uint32_t> MeshBuilder::Private::reindex()
        {
            std::vector<std::uint32_t> indices;

            if (indicesCount == 0)
            {
                indices = std::vector<std::uint32_t>(positionsCount);
                std::iota(indices.begin(), indices.end(), 0);
                return indices;
            }

            indexMap.clear();
            for (std::size_t i = 0; i < indicesCount; i++)
            {
                std::array<std::size_t, 4> indexGroup = {
                    (positionIndices ? static_cast<std::size_t>(positionIndices[i]) : 0),
                    (normalIndices ? static_cast<std::size_t>(normalIndices[i]) : 0),
                    (colorIndices ? static_cast<std::size_t>(colorIndices[i]) : 0),
                    (texCoordIndices ? static_cast<std::size_t>(texCoordIndices[i]) : 0)
                };

                auto it = indexMap.find(indexGroup);

                int index;
                if (it == indexMap.end())
                {
                    index = static_cast<std::uint32_t>(indices.size());
                    indexMap.emplace(indexGroup, index);
                }
                else
                {
                    index = it->second;
                }

                indices.push_back(index);
            }

            return indices;
        }

        void MeshBuilder::Private::buildVertexArray(Rendering::Mesh &mesh) const
        {
            mesh.getVertexBuffer()->resize(indicesCount * mesh.getLayout().getTotalStride());
            mesh.setVertexCount(indexMap.size());
            mesh.setPrimitiveCount(indicesCount);

            Rendering::VertexArray vertexArray(mesh.getVertexBuffer(), mesh.getLayout());

            // FIXME un-hardcode
            Rendering::VertexComponentArray positionsArray = vertexArray.get("mdl_Position");
            Rendering::VertexComponentArray normalsArray = vertexArray.get("mdl_Normal");
            Rendering::VertexComponentArray colorsArray = vertexArray.get("mdl_Color");
            Rendering::VertexComponentArray texCoordsArray = vertexArray.get("mdl_TexCoords");

            for (const auto &indices : indexMap)
            {
                const std::array<std::size_t, 4> &indexGroup = indices.first;
                std::size_t finalIndex = indices.second;

                positionsArray.at(finalIndex).copyFrom(positions + (3 * indexGroup[0]));

                if (normals)
                {
                    normalsArray.at(finalIndex).copyFrom(normals + (3 * indexGroup[1]));
                }
                if (colors)
                {
                    colorsArray.at(finalIndex).copyFrom(colors + (3 * indexGroup[2]));
                }
                if (texCoords)
                {
                    texCoordsArray.at(finalIndex).copyFrom(texCoords + (2 * indexGroup[3]));
                }
            }
        }
    }
}
