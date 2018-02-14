#ifndef IMODELLOADER_H
#define IMODELLOADER_H

#include <vector>

#include "Amber/Core/Entity.h"

namespace Amber
{
    namespace IO
    {
        class IModelLoader
        {
            public:
                virtual ~IModelLoader() = default;

                virtual std::vector<Core::Entity> loadModel(const std::string &fileName) = 0;
        };
    }
}

#endif // IMODELLOADER_H
