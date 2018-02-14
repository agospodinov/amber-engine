#ifndef CLASSTYPEID_H
#define CLASSTYPEID_H

#include <atomic>

namespace Amber
{
    namespace Utilities
    {
        using TypeId = std::size_t;

        template <typename TBase>
        class ClassTypeId
        {
            public:
                ClassTypeId() = delete;
                ~ClassTypeId() = default;

                template <typename TDerived>
                static TypeId typeId()
                {
                    static_assert(std::is_base_of<TBase, TDerived>::value, "Cannot get ClassTypeId of unrelated class");

                    static TypeId id = nextTypeId++;
                    return id;
                }

            private:
                static std::atomic<TypeId> nextTypeId;
        };

        template <typename TBase>
        std::atomic<TypeId> ClassTypeId<TBase>::nextTypeId(0);
    }
}

#endif // CLASSTYPEID_H
