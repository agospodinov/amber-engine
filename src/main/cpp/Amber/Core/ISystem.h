#ifndef ISYSTEM_H
#define ISYSTEM_H

namespace Amber
{
    namespace Core
    {
        class ISystem
        {
            public:
                ISystem() = default;
                virtual ~ISystem() = default;

                virtual bool isOnSeparateThread() const = 0;

                virtual void runSingleIteration() = 0;
                virtual void run() = 0;
        };
    }
}

#endif // ISYSTEM_H
