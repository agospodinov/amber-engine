#ifndef COLLADAMODELLOADER_H
#define COLLADAMODELLOADER_H

#include "Utilities/Config.h"
#ifdef OpenCOLLADA_FOUND

#include "IModelLoader.h"

namespace Amber
{
    namespace IO
    {
        class ColladaModelLoader : public IModelLoader
        {
            public:
                ColladaModelLoader() = default;
                virtual ~ColladaModelLoader() = default;

                virtual Rendering::Model loadModel(const std::string &fileName) override final;

            private:
                class OCLoader;
        };
    }
}

#endif

#endif // COLLADAMODELLOADER_H
