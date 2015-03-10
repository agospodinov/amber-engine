#ifndef AMBERMODELLOADER_H
#define AMBERMODELLOADER_H

#include "IModelLoader.h"

namespace Amber
{
    namespace IO
    {
        class AmberModelLoader : public IModelLoader
        {
            public:
                AmberModelLoader() = default;

                Rendering::Model loadModel(const std::string &fileName);
        };
    }
}

#endif // AMBERMODELLOADER_H
