#ifndef ENTITY_H
#define ENTITY_H

#include <algorithm>
#include <memory>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "Amber/Core/IComponent.h"
#include "Amber/Utilities/ClassTypeId.h"

namespace Amber
{
    namespace Core
    {
        class Entity
        {
            public:
                template <typename... Ts>
                class Proxy
                {
                    public:
                        template <typename U>
                        U *get()
                        {
                            return std::get<U *>(components);
                        }

                        bool isValid()
                        {
                            bool valid[] = { (std::get<Ts *>(components) != nullptr)... };
                            return std::all_of(std::begin(valid), std::end(valid), [] (bool b) { return b; });
                        }

                    private:
                        friend class Entity;

                        Proxy(std::tuple<Ts *...> components)
                            : components(components)
                        {
                        }

                        std::tuple<Ts *...> components;
                };

                Entity() = default;
                Entity(const Entity &other) = delete;
                Entity(Entity &&other) noexcept;
                ~Entity() = default;

                Entity &operator =(const Entity &other) = delete;
                Entity &operator =(Entity &&other) noexcept;

                template <typename... Ts>
                Entity::Proxy<Ts...> getProxy()
                {
                    return Proxy<Ts...>(std::make_tuple(getComponent<Ts>()...));
                }

                template <typename T>
                bool hasComponent() const
                {
                    return getComponent<T>() != nullptr;
                }

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
