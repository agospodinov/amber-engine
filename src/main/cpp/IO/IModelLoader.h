#ifndef IMODELLOADER_H
#define IMODELLOADER_H

#include "Rendering/Model.h"

namespace Amber
{
    namespace IO
    {
        class IModelLoader
        {
            public:
                virtual ~IModelLoader() = default;

                virtual Rendering::Model loadModel(const std::string &fileName) = 0;
        };
    }
}

#endif // IMODELLOADER_H
