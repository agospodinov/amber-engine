#ifndef AMBERMODELLOADER_H
#define AMBERMODELLOADER_H

#include "Amber/IO/IModelLoader.h"

#include <vector>

#include "Amber/Core/Entity.h"

namespace Amber
{
    namespace IO
    {
        class AmberModelLoader : public IModelLoader
        {
            public:
                AmberModelLoader() = default;

                virtual std::vector<Core::Entity> loadModel(const std::string &fileName);
        };
    }
}

#endif // AMBERMODELLOADER_H
