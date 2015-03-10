#include "MeshBuilder.h"

namespace Amber
{
    namespace IO
    {
        class MeshBuilder::Private
        {
            public:
                Private();

                std::vector<std::uint32_t> reindex();

                template <typename T>
                void buildVertexArray(Rendering::Mesh &mesh) const;

                template <typename T>
                void buildPositions(T *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const;

                template <typename T>
                void buildNormals(T *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const;

                template <typename T>
                void buildColors(T *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const;

                template <typename T>
                void buildTexCoords(T *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const;

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
            Rendering::Mesh mesh;

            std::vector<std::uint32_t> indices = p->reindex();
            if (mesh.getIndexBuffer().isValid())
            {
                Rendering::IBuffer &indexBuffer = *mesh.getIndexBuffer();
                indexBuffer.resize(indices.size() * sizeof(std::uint32_t));
                indexBuffer.assign(0, indices.size() * sizeof(std::uint32_t), indices.data());
            }

            if (p->positions && !p->normals && !p->colors && !p->texCoords)
            {
                p->buildVertexArray<Rendering::Vertex::Position>(mesh);
            }
            else if (p->positions && p->normals && !p->colors && !p->texCoords)
            {
                p->buildVertexArray<Rendering::Vertex::PositionNormal>(mesh);
            }
            else if (p->positions && p->normals && p->colors && !p->texCoords)
            {
                p->buildVertexArray<Rendering::Vertex::PositionNormalColor>(mesh);
            }
            else if (p->positions && p->normals && !p->colors && p->texCoords)
            {
                p->buildVertexArray<Rendering::Vertex::PositionNormalUV>(mesh);
            }
            else
            {
                throw std::runtime_error("Unsupported vertex type.");
            }

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

        template <typename T>
        void MeshBuilder::Private::buildVertexArray(Rendering::Mesh &mesh) const
        {
            static_assert(Rendering::Vertex::IsVertexType<T>::value, "Must supply a supported vertex type.");

            mesh.getVertexBuffer()->resize(indicesCount * sizeof(T));
            Utilities::ScopedDataPointer p = mesh.getVertexBuffer()->data();
            T *vertexArray = static_cast<T *>(p.get());

            for (const auto &indexGroup : indexMap)
            {
                buildPositions(vertexArray, indexGroup.first, indexGroup.second);
                buildNormals(vertexArray, indexGroup.first, indexGroup.second);
                buildColors(vertexArray, indexGroup.first, indexGroup.second);
                buildTexCoords(vertexArray, indexGroup.first, indexGroup.second);
            }

            mesh.setVertexCount(indexMap.size());
            mesh.setPrimitiveCount(indicesCount);
            mesh.setLayout(std::make_shared<Rendering::Layout>(Rendering::Layout::getStandardLayout<T>()));
        }

        template <typename T>
        void MeshBuilder::Private::buildPositions(T *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const
        {
            assert(indexGroup[0] >= 0 && indexGroup[0] < positionsCount);

            vertexArray[index].x = positions[3 * indexGroup[0] + 0];
            vertexArray[index].y = positions[3 * indexGroup[0] + 1];
            vertexArray[index].z = positions[3 * indexGroup[0] + 2];
        }

        template <typename T>
        void MeshBuilder::Private::buildNormals(T *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const
        {
            assert(indexGroup[1] >= 0 && indexGroup[1] < normalsCount);

            vertexArray[index].nx = normals[3 * indexGroup[1] + 0];
            vertexArray[index].ny = normals[3 * indexGroup[1] + 1];
            vertexArray[index].nz = normals[3 * indexGroup[1] + 2];
        }

        template <>
        void MeshBuilder::Private::buildNormals(Rendering::Vertex::Position *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const
        {
        }

        template <typename T>
        void MeshBuilder::Private::buildColors(T *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const
        {
        }

        template <>
        void MeshBuilder::Private::buildColors(Rendering::Vertex::PositionNormalColor *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const
        {
            assert(indexGroup[2] >= 0 && indexGroup[2] < colorsCount);

            vertexArray[index].r = static_cast<std::uint8_t>(colors[3 * indexGroup[2] + 0] * 255);
            vertexArray[index].g = static_cast<std::uint8_t>(colors[3 * indexGroup[2] + 1] * 255);
            vertexArray[index].b = static_cast<std::uint8_t>(colors[3 * indexGroup[2] + 2] * 255);
            vertexArray[index].a = 255;
        }

        template <typename T>
        void MeshBuilder::Private::buildTexCoords(T *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const
        {
        }

        template <>
        void MeshBuilder::Private::buildTexCoords(Rendering::Vertex::PositionNormalUV *vertexArray, const std::array<std::size_t, 4> &indexGroup, std::size_t index) const
        {
            assert(indexGroup[3] >= 0 && indexGroup[3] < texCoordsCount);

            vertexArray[index].u = texCoords[2 * indexGroup[3] + 0];
            vertexArray[index].v = texCoords[2 * indexGroup[3] + 1];
        }
    }
}
