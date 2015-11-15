#ifndef ICOMPONENT_H
#define ICOMPONENT_H

namespace Amber
{
    namespace Core
    {
        class IComponent
        {
            public:
                enum class Type
                {
                    Model,
                    Light,
                    Camera,
                    Skeleton
                };

                IComponent() = default;
                virtual ~IComponent() = default;

                virtual Type getType() = 0;

                virtual bool isSetup() const = 0;
        };
    }
}

#endif // ICOMPONENT_H
