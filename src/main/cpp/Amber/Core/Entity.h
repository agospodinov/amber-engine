#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <unordered_map>

#include "Amber/Core/IComponent.h"
#include "Amber/Utilities/ClassTypeId.h"

namespace Amber
{
    namespace Core
    {
        class Entity
        {
            public:
                Entity() = default;
                Entity(const Entity &other) = delete;
                Entity(Entity &&other) noexcept;
                ~Entity() = default;

                Entity &operator =(const Entity &other) = delete;
                Entity &operator =(Entity &&other) noexcept;

                template <typename T>
                const T *getComponent() const
                {
                    using Amber::Utilities::ClassTypeId;
                    auto it = components.find(ClassTypeId<IComponent>::typeId<T>());
                    return it == components.end() ? nullptr : static_cast<T *>(it->second.get());
                }

                template <typename T>
                T *getComponent()
                {
                    using Amber::Utilities::ClassTypeId;
                    auto it = components.find(ClassTypeId<IComponent>::typeId<T>());
                    return it == components.end() ? nullptr : static_cast<T *>(it->second.get());
                }

                template <typename T>
                void addComponent(std::unique_ptr<T> component)
                {
                    static_assert(std::is_base_of<IComponent, T>::value, "Object does not implement IComponent");
                    using Amber::Utilities::ClassTypeId;

                    components.emplace(ClassTypeId<IComponent>::typeId<T>(), std::move(component));
                }

            private:
                std::unordered_map<Amber::Utilities::TypeId, std::unique_ptr<IComponent>> components;
        };
    }
}

#endif // ENTITY_H
