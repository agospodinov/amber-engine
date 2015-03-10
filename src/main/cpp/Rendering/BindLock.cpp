#include "BindLock.h"

#include <mutex>

namespace Amber
{
    namespace Rendering
    {
        BindLock::BindLock()
            : locked(false)
        {
        }

        BindLock::BindLock(Reference<IBindable> bindable)
            : bindable(bindable),
              locked(false)
        {
            lock();
        }

        BindLock::BindLock(const BindLock &other)
            : bindable(other.bindable),
              locked(other.locked)
        {
            acquireContextLock();
        }

        BindLock::BindLock(BindLock &&other) noexcept
        {
            using std::swap;
            swap(bindable, other.bindable);
            swap(locked, other.locked);
        }

        BindLock::~BindLock()
        {
            unlock();
        }

        BindLock &BindLock::operator =(const BindLock &other)
        {
            bindable = other.bindable;
            locked = other.locked;

            acquireContextLock();

            return *this;
        }

        BindLock &BindLock::operator =(BindLock &&other) noexcept
        {
            using std::swap;
            swap(bindable, other.bindable);
            swap(locked, other.locked);

            return *this;
        }

        void BindLock::lock()
        {
            if (!locked && bindable.isValid())
            {
                acquireContextLock();
                bindable->bind();
                locked = true;
            }
        }

        void BindLock::unlock()
        {
            if (locked && bindable.isValid())
            {
                bindable->unbind();
                releaseContextLock();
                locked = false;
            }
        }

        void BindLock::acquireContextLock()
        {
            bindable.getContext()->lock(bindable);
        }

        void BindLock::releaseContextLock()
        {
            bindable.getContext()->unlock(bindable);
        }
    }
}
