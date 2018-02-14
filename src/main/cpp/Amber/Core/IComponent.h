#ifndef ICOMPONENT_H
#define ICOMPONENT_H


namespace Amber
{
    namespace Core
    {
        class IComponent
        {
            public:
                IComponent() = default;
                virtual ~IComponent() = default;
        };
    }
}
#endif // ICOMPONENT_H
