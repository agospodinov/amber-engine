#ifndef VERTEXTYPES_H
#define VERTEXTYPES_H

#include "Utilities/ScopedDataPointer.h"
#include "IBuffer.h"
#include "Layout.h"
#include "Reference.h"

namespace Amber
{
    namespace Rendering
    {
        class Vertex
        {
            public:
                void copyFrom(const float *data);
                void copyFrom(const double *data);
                void copyFrom(const std::int8_t *data);
                void copyFrom(const std::int16_t *data);
                void copyFrom(const std::int32_t *data);
                void copyFrom(const std::uint8_t *data);
                void copyFrom(const std::uint16_t *data);
                void copyFrom(const std::uint32_t *data);

            private:
                friend class VertexComponentArray;
                Vertex(std::uint8_t *vertexData, const Layout::Attribute *attribute);

                template <typename InputType>
                void optimalCopy(const InputType *inputData, Layout::ComponentType inputType);

                template <typename InputType, typename DestinationType>
                void transform(const InputType *data);

                std::uint8_t *vertexData;
                const Layout::Attribute *attribute;
        };

        class VertexComponentArray
        {
            public:
                bool isValid() const;

                Vertex at(std::size_t index);

            private:
                friend class VertexArray;
                VertexComponentArray(std::uint8_t *subdata, const Layout::Attribute *attribute);

                std::uint8_t *subdata;
                const Layout::Attribute *attribute;

        };

        class VertexArray
        {
            public:
                VertexArray(Reference<IBuffer> buffer, Layout layout);

                VertexComponentArray get(const std::string &name) const;

            private:
                friend class VertexComponentArray;

                Utilities::ScopedDataPointer data;
                const Layout layout;
        };
    }
}

#endif // VERTEXTYPES_H
