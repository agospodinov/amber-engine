#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <istream>
#include <memory>
#include <string>

namespace Amber
{
    namespace IO
    {
        class AssetManager
        {
            public:
                AssetManager() = default;
                ~AssetManager() = default;

                std::istream open(const std::string &fileName);

            private:
                class Private;
                std::unique_ptr<Private> p;
        };
    }
}

#endif // ASSETMANAGER_H
