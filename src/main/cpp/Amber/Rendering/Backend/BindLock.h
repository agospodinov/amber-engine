#ifndef BINDLOCK_H
#define BINDLOCK_H

#include "Amber/Rendering/Backend/IBindable.h"
#include "Amber/Rendering/Backend/Reference.h"

namespace Amber
{
    namespace Rendering
    {
        class BindLock
        {
            public:
                BindLock();
                BindLock(Reference<IBindable> bindable);
                BindLock(const BindLock &other);
                BindLock(BindLock &&other) noexcept;
                ~BindLock();

                BindLock &operator =(const BindLock &other);
                BindLock &operator =(BindLock &&other) noexcept;

                void lock();
                void unlock();

            private:
                void acquireContextLock();
                void releaseContextLock();

                Reference<IBindable> bindable;
                bool locked;
        };
    }
}

#endif // BINDLOCK_H
