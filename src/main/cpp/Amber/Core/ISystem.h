#ifndef ISYSTEM_H
#define ISYSTEM_H

#include "Amber/Core/Entity.h"

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

                virtual void registerEntity(Entity &entity) = 0;

            protected:
                template <typename... Ts, typename F>
                static void registerProxy(Entity &entity, F f)
                {
                    Entity::Proxy<Ts...> proxy = entity.getProxy<Ts...>();
                    if (proxy.isValid())
                    {
                        f(proxy);
                    }
                }
        };
    }
}

#endif // ISYSTEM_H
