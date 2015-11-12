#ifndef SCOPEDDATAPOINTER_H
#define SCOPEDDATAPOINTER_H

#include <functional>

namespace Amber
{
    namespace Utilities
    {
        struct NoOpDeleter
        {
            public:
                void operator()(void *) {}
        };

        class ScopedDataPointer
        {
            public:
                typedef std::function<void(void *)> Deleter;

                ScopedDataPointer(void *data, Deleter deleter = NoOpDeleter())
                    : data(data),
                      deleter(deleter)
                {
                }

                ~ScopedDataPointer()
                {
                    deleter(data);
                }

                inline void *get()
                {
                    return data;
                }

                inline void *get() const
                {
                    return data;
                }

            private:
                void *data;
                Deleter deleter;
        };

    }
}

#endif // SCOPEDDATAPOINTER_H
