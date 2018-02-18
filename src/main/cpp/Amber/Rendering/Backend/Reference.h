#ifndef REFERENCE_H
#define REFERENCE_H

#include "Amber/Rendering/Backend/IContext.h"

namespace Amber
{
    namespace Rendering
    {
        template <typename ValueType>
        class Reference
        {
            public:
                Reference();
                Reference(IContext *context, ValueType *value);
                Reference(const Reference &other) noexcept = default;
                Reference(Reference &&other) noexcept = default;
                ~Reference() = default;

                Reference &operator =(const Reference &other) noexcept = default;
                Reference &operator =(Reference &&other) noexcept = default;

                ValueType *operator->();
                const ValueType *operator->() const;

                ValueType &operator*();
                const ValueType &operator*() const;

                ValueType *get();
                ValueType *get() const;

                IContext *getContext() const;

                template <typename NewType>
                Reference<NewType> cast() const;

                template <typename NewType>
                operator Reference<NewType>() const;

                bool isValid() const;

            private:
                void checkValid() const;

                IContext *context;
                ValueType *value;
        };

        template <typename ValueType>
        bool operator==(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs);

        template <typename ValueType>
        bool operator!=(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs);

        template <typename ValueType>
        bool operator<(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs);

        template <typename ValueType>
        bool operator>(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs);

        template <typename ValueType>
        bool operator<=(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs);

        template <typename ValueType>
        bool operator>=(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs);
    }
}

#include "Amber/Rendering/Backend/Reference.txx"

#endif // REFERENCE_H
