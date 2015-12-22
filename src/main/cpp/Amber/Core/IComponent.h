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
                    Mesh,
                    Material,
                    Light,
                    Camera,
                    Skeleton
                };

                IComponent() = default;
                virtual ~IComponent() = default;

                virtual Type getType() const = 0;

                virtual bool isSetup() const = 0;
        };
    }
}

#endif // ICOMPONENT_H
