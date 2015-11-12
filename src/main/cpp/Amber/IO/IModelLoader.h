#ifndef IMODELLOADER_H
#define IMODELLOADER_H

#include <memory>

#include "Amber/Rendering/Node.h"

namespace Amber
{
    namespace IO
    {
        class IModelLoader
        {
            public:
                virtual ~IModelLoader() = default;

                virtual std::unique_ptr<Rendering::Node> loadModel(const std::string &fileName) = 0;
        };
    }
}

#endif // IMODELLOADER_H
