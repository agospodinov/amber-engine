#include "Reference.h"

#include <tuple>

namespace Amber
{
    namespace Rendering
    {
        template <typename ValueType>
        Reference<ValueType>::Reference()
            : Reference(nullptr, nullptr)
        {
        }

        template <typename ValueType>
        Reference<ValueType>::Reference(IContext *context, ValueType *value)
            : context(context),
              value(value)
        {
        }

        template <typename ValueType>
        ValueType *Reference<ValueType>::operator->()
        {
            return get();
        }

        template <typename ValueType>
        const ValueType *Reference<ValueType>::operator->() const
        {
            return get();
        }

        template <typename ValueType>
        ValueType &Reference<ValueType>::operator*()
        {
            return *get();
        }

        template <typename ValueType>
        const ValueType &Reference<ValueType>::operator*() const
        {
            return *get();
        }

        template <typename ValueType>
        ValueType *Reference<ValueType>::get()
        {
            checkValid();
            return value;
        }

        template <typename ValueType>
        ValueType *Reference<ValueType>::get() const
        {
            checkValid();
            return value;
        }

        template <typename ValueType>
        IContext *Reference<ValueType>::getContext() const
        {
            checkValid();
            return context;
        }

        template <typename ValueType>
        template <typename NewType>
        Reference<NewType> Reference<ValueType>::cast() const
        {
            NewType *newValue = dynamic_cast<NewType *>(value);
            return (newValue != nullptr) ? Reference<NewType>(context, newValue) : Reference<NewType>();
        }

        template <typename ValueType>
        bool Reference<ValueType>::isValid() const
        {
            IContext *activeContext = IContext::getActiveContext();
            return activeContext != nullptr && context == activeContext && value != nullptr;
        }

        template <typename ValueType>
        void Reference<ValueType>::checkValid() const
        {
            if (!isValid())
            {
                throw std::runtime_error("Accessing invalid reference.");
            }
        }

        template <typename ValueType>
        bool operator==(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs)
        {
            return lhs.getContext() == rhs.getContext() && lhs.get() == rhs.get();
        }

        template <typename ValueType>
        bool operator!=(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs)
        {
            return !(lhs == rhs);
        }

        template <typename ValueType>
        bool operator<(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs)
        {
            return std::make_pair(lhs.getContext(), lhs.get()) < std::make_pair(rhs.getContext(), rhs.get());
        }

        template <typename ValueType>
        bool operator>(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs)
        {
            return rhs < lhs;
        }

        template <typename ValueType>
        bool operator<=(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs)
        {
            return !(lhs > rhs);
        }

        template <typename ValueType>
        bool operator>=(const Reference<ValueType> &lhs, const Reference<ValueType> &rhs)
        {
            return !(lhs < rhs);
        }
    }
}
